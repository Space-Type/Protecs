/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Implementation for
** EntityComponentData packet
*/

#include "EntityComponentData.hpp"
#include <protecs/errors.hpp>
#include <protecs/utils.hpp>


static Protecs::Components::Variant deserializeComponent(std::size_t type, std::span<const std::uint8_t> input);


void Protecs::Networking::Packets::EntityComponentData::serialize(std::span<std::uint8_t> output) const
{
    auto* current = output.data();

    Utils::copyFromValue(current, entity);
    Utils::copyFromValue(current, component);
}

auto Protecs::Networking::Packets::EntityComponentData::deserialize(std::span<const std::uint8_t> input) -> EntityComponentData
{
    const auto* current = input.data();
    EntityComponentData result;
    std::uint16_t type;

    Utils::copyToValue(result.entity, current);
    Utils::copyToValue(type, current);
    result.component = ::deserializeComponent(type, std::span(std::span<const std::uint8_t>::const_iterator(current), input.cend()));

    return result;
}


#define index_of(type) Wrecks::Utils::element_index_v<Protecs::Components::type, Protecs::Components::Variant>


Protecs::Components::Variant deserializeComponent(std::size_t type, std::span<const std::uint8_t> input)
{
    const auto* current = input.data();

    switch (type) {
        case index_of(Transform): return Protecs::Components::Transform::deserialize(current, input.size());
        case index_of(Velocity):  return Protecs::Components::Velocity::deserialize(current, input.size());

        default: throw Protecs::PacketError("unknown component type in entity component data packet");
    }
}
