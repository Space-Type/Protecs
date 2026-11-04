/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Implementation for
** Packet struct
*/

#include "Packet.hpp"
#include <protecs.hpp>


auto Protecs::Networking::Packet::serialize(const Packets::PacketData& data) -> Packet
{
    Packet packet = {};

    auto current = packet.raw.begin();
    *current = static_cast<std::uint8_t>(data.index());
    ++current;

    std::visit([&](const auto& data){
        data.serialize(std::span(current, packet.raw.end()));
        std::advance(current, data.packedSize());
    }, data);

    auto bytesFilled = std::distance(packet.raw.begin(), current);
    packet.filled = bytesFilled >= 0
        ? static_cast<std::size_t>(bytesFilled)
        : 0;

    return packet;
}


auto Protecs::Networking::Packet::deserialize() const -> Packets::PacketData
{
    auto dataStart = raw.cbegin();
    auto dataEnd = raw.cbegin();
    std::advance(dataEnd, filled);

    std::uint8_t typeIndex = *dataStart;
    ++dataStart;

    Packets::PacketData result;

    try {
        Wrecks::Utils::visitType<Packets::PacketData>([&](auto type){
            using PacketType = typename decltype(type)::type;
            result = PacketType::deserialize(std::span(dataStart, dataEnd));
        }, typeIndex);
    } catch (std::out_of_range) {
        throw SerializationError("unknown packet data type " + std::to_string(typeIndex));
    }

    return result;
}

std::ostream& operator<<(std::ostream& stream, const Protecs::Networking::Packet& packet)
{
    std::uint8_t typeIndex = packet.raw[0];
    std::string_view name = packet.filled == 0
        ? "unknown"
        : std::string_view();

    if (name.empty()) {
        try {
            Wrecks::Utils::visitType<Protecs::Networking::Packets::PacketData>([&](auto type){
                using PacketType = typename decltype(type)::type;
                name = PacketType::packetName();
            }, typeIndex);
        } catch (std::out_of_range) {
            name = "unknown";
        }
    }

    return stream << name << " packet "
                  << "(" << packet.filled << "B)";
}
