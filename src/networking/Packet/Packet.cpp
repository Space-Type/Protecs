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


#define index_of(type) Wrecks::Utils::element_index_v<Packets::type, Packets::PacketData>


auto Protecs::Networking::Packet::deserialize() const -> Packets::PacketData
{
    Packets::PacketData result;

    auto dataStart = raw.cbegin();
    auto dataEnd = raw.cbegin();
    std::advance(dataEnd, filled);

    std::uint8_t type = *dataStart;
    ++dataStart;

    switch (type) {
        case index_of(EntityComponentData):
            result = Packets::EntityComponentData::deserialize(std::span(dataStart, dataEnd));
            break;

        case index_of(EntityCreate):
            result = Packets::EntityCreate::deserialize(std::span(dataStart, dataEnd));
            break;

        case index_of(EntityDelete):
            result = Packets::EntityDelete::deserialize(std::span(dataStart, dataEnd));
            break;

        case index_of(EntityRemoveComponent):
            result = Packets::EntityRemoveComponent::deserialize(std::span(dataStart, dataEnd));
            break;

        case index_of(EntitySyncComponents):
            result = Packets::EntitySyncComponents::deserialize(std::span(dataStart, dataEnd));
            break;

        case index_of(Ping):
            result = Packets::Ping::deserialize(std::span(dataStart, dataEnd));
            break;

        case index_of(PlayerId):
            result = Packets::PlayerId::deserialize(std::span(dataStart, dataEnd));
            break;

        case index_of(PlayerInput):
            result = Packets::PlayerInput::deserialize(std::span(dataStart, dataEnd));
            break;

        case index_of(PlayerJoin):
            result = Packets::PlayerJoin::deserialize(std::span(dataStart, dataEnd));
            break;

        case index_of(PlayerLeave):
            result = Packets::PlayerLeave::deserialize(std::span(dataStart, dataEnd));
            break;

        default: throw PacketError("unknown packet data type " + std::to_string(type));
    }

    return result;
}
