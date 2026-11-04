/*
** EPITECH PROJECT, 2026
** Project - PacketQueue
** File description:
** Implementation for
** PacketQueue class
*/

#include "PacketQueue.hpp"
#include <algorithm>
#include <mutex>
#include <protecs/errors.hpp>
#include <variant>


template <typename T>
concept SimulationTickPacket = requires (const T& packet)
{
    { packet.simulationTick } -> std::convertible_to<Protecs::Tick>;
};

template <typename T>
concept SequencePacket = SimulationTickPacket<T> && requires (const T& packet)
{
    { packet.sequence } -> std::convertible_to<std::uint8_t>;
};


Protecs::Networking::PacketQueue::PacketQueue(PacketQueue&& other)
    : PacketQueue()
{
    swap(other);
}


/**
 * Returns the first simulation
 * for which an event exists.
 *
 * Note:
 * If no packets exist, or if a
 * packet with no specified tick
 * exists, 0 is returned.
 */
auto Protecs::Networking::PacketQueue::firstTick() const -> Tick
{
    std::scoped_lock lock(m_BufferLock);

    if (m_Buffer.empty())
        return 0;

    const auto& element = m_Buffer.back();

    Packets::PacketData packetData;
    try {
        packetData = element.second.deserialize();
    } catch (const SerializationError&) {
        return 0;
    }

    return std::visit([&](const auto& data) -> Tick {
        using PacketType = std::decay_t<decltype(data)>;
        if constexpr (SimulationTickPacket<PacketType>) {
            return data.simulationTick;
        } else {
            return 0;
        }
    }, packetData);
}

/**
 * Creates a new packet from
 * the given data and pushes
 * it onto the queue. For more
 * information, please refer
 * on the main overload for push().
 */
void Protecs::Networking::PacketQueue::push(const Address& addr, Packets::PacketData&& data)
{
    push(addr, Packet::serialize(std::move(data)));
}

/**
 * Pushes the specified packet
 * into its appropriate place
 * in the queue, which depends
 * on the packet's priority.
 *
 * Note:
 * The front of the vector is the
 * packet with the least priority.
 */
void Protecs::Networking::PacketQueue::push(const Address& addr, const Packet& packet)
{
    std::scoped_lock lock(m_BufferLock);

    if (m_Buffer.empty()) {
        m_Buffer.emplace_back(addr, packet);
        return;
    }

    std::pair<Address, Packet> data = { addr, packet };
    auto loc = std::upper_bound(m_Buffer.cbegin(), m_Buffer.cend(), data, hasHigherPriority);
    m_Buffer.insert(loc, std::move(data));
}

/**
 * Pops the first available packet (if any).
 *
 * Note:
 * The back of the vector (i.e. the
 * packet that's getting popped) is
 * the packet with the most priority.
 */
auto Protecs::Networking::PacketQueue::pop() -> std::optional<Element>
{
    std::scoped_lock lock(m_BufferLock);
    std::optional<Element> result;

    if (m_Buffer.empty())
        return result;

    result = std::move(m_Buffer.back());
    m_Buffer.pop_back();
    return result;
}

/**
 * Swaps the container's data with
 * the data of the given queue.
 *
 * Note:
 * This function sis thread-safe.
 */
void Protecs::Networking::PacketQueue::swap(PacketQueue& other)
{
    std::scoped_lock lock(m_BufferLock, other.m_BufferLock);
    m_Buffer.swap(other.m_Buffer);
}


template <typename TA>
struct PacketPriority {
    const TA& a;

    template <typename TB>
    requires (SequencePacket<TA> && SequencePacket<TB>)
    bool operator()(const TB& b)
    {
        // A has a simulation tick and sequence nb
        // B has a simulation tick and sequence nb
        // -> The one with a smaller tick AND smaller sequence has higher priority
        if (a.simulationTick != b.simulationTick)
            return a.simulationTick < b.simulationTick;

        return a.sequence < b.sequence;
    }

    template <typename TB>
    requires (SequencePacket<TA> && SimulationTickPacket<TB>)
    bool operator()(const TB& b)
    {
        // A has a simulation tick and sequence nb
        // B has a simulation tick and no sequence nb
        // -> The one with smaller tick has higher priority, but if equal then A has priority
        if (a.simulationTick == b.simulationTick)
            return true;

        return a.simulationTick < b.simulationTick;
    }

    template <typename TB>
    requires (SimulationTickPacket<TA> && SequencePacket<TB>)
    bool operator()(const TB& b)
    {
        // A has a simulation tick and no sequence nb
        // B has a simulation tick and sequence nb
        // -> The one with smaller tick has higher priority, but if equal then B has priority
        if (a.simulationTick == b.simulationTick)
            return false;

        return a.simulationTick < b.simulationTick;
    }

    template <typename TB>
    requires (SimulationTickPacket<TA> && SimulationTickPacket<TB>)
    bool operator()(const TB& b)
    {
        // A has a simulation tick
        // B has a simulation tick
        // -> The one with a smaller tick has higher priority
        return a.simulationTick < b.simulationTick;
    }

    template <typename TB>
    requires (SimulationTickPacket<TA>)
    bool operator()(const TB& b)
    {
        // A has a simulation tick
        // B has no simulation tick
        // -> B has higher priority
        return false;
    }

    template <typename TB>
    requires (SimulationTickPacket<TB>)
    bool operator()(const TB& b)
    {
        // A has no simulation tick
        // B has a simulation tick
        // -> A has higher priority
        return true;
    }

    template <typename TB>
    bool operator()(const TB& b)
    {
        // A has no simulation tick
        // B has no simulation tick
        // -> Same priority (B higher
        //    priority since it requires
        //    less work)
        return false;
    }
};

/**
 * Determines if a packet has a higher
 * priority than another packet.
 *
 * Note:
 * Invalid packets have highest priority,
 * such that the error can get handled
 * swiftly before moving on.
 */
bool Protecs::Networking::PacketQueue::hasHigherPriority(const Element& a, const Element& b) noexcept
{
    Packets::PacketData dataA;
    Packets::PacketData dataB;
    bool isValidA = true;
    bool isValidB = true;

    try {
        dataA = a.second.deserialize();
    } catch (const SerializationError&) {
        isValidA = false;
    }

    try {
        dataB = b.second.deserialize();
    } catch (const SerializationError&) {
        isValidB = false;
    }

    if (!isValidA || !isValidB)
        return !isValidA || isValidB;

    return std::visit([&](const auto& b){
        return std::visit(PacketPriority{ b }, dataA);
    }, dataB);
}
