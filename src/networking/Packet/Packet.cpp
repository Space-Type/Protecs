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
        throw PacketError("unknown packet data type " + std::to_string(typeIndex));
    }

    return result;
}
