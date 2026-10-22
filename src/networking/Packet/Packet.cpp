/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Implementation for
** Packet struct
*/

#include "Packet.hpp"
#include <protecs.hpp>


#define index_of(type) Wrecks::Utils::element_index_v<Packets::type, Packets::PacketData>


auto Protecs::Networking::Packet::serialize(const Packets::PacketData& data) -> Packet
{
    Packet packet = {};

    auto dataStart = packet.raw.begin();
    *dataStart = static_cast<std::uint8_t>(data.index());
    ++dataStart;

    std::visit([&](const auto& data){
        data.serialize(std::span(dataStart, packet.raw.end()));
    }, data);

    return packet;
}

auto Protecs::Networking::Packet::deserialize(std::size_t bytes) const -> Packets::PacketData
{
    Packets::PacketData result;

    auto dataStart = raw.cbegin();
    auto dataEnd = raw.cbegin();
    std::advance(dataEnd, bytes);

    std::uint8_t type = *dataStart;
    ++dataStart;

    switch (type) {
        case index_of(EntityAddComponent):
            result = Packets::EntityAddComponent::deserialize(std::span(dataStart, dataEnd));
            break;

        case index_of(EntityComponentData):
            result = Packets::EntityComponentData::deserialize(std::span(dataStart, dataEnd));
            break;

        case index_of(EntityRemoveComponent):
            result = Packets::EntityRemoveComponent::deserialize(std::span(dataStart, dataEnd));
            break;

        case index_of(EntitySyncComponents):
            result = Packets::EntitySyncComponents::deserialize(std::span(dataStart, dataEnd));
            break;

        case index_of(PlayerInput):
            result = Packets::PlayerInput::deserialize(std::span(dataStart, dataEnd));
            break;

        default: throw PacketError("unknown packet data type " + std::to_string(type));
    }

    return result;
}
