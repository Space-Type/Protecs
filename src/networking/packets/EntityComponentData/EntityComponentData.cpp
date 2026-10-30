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
    if (output.size() < packedSize())
        throw SerializationError("unable to serialize EntityComponentData packet as the output buffer is too small");

    auto* current = output.data();
    std::uint16_t type = static_cast<std::uint16_t>(component.index());

    Utils::copyFromValue(current, entity);
    Utils::copyFromValue(current, type);

    std::size_t remainingSize = output.size() - (current - output.data());

    std::visit([=, &current](const auto& component){
        component.serialize(current, remainingSize);
    }, component);
}

auto Protecs::Networking::Packets::EntityComponentData::deserialize(std::span<const std::uint8_t> input) -> EntityComponentData
{
    if (input.size() < partialPackedSize())
        throw SerializationError("unable to deserialize EntityComponentData packet as the input buffer is too small");

    const auto* current = input.data();
    EntityComponentData result;
    std::uint16_t type;

    Utils::copyToValue(result.entity, current);
    Utils::copyToValue(type, current);
    result.component = ::deserializeComponent(type, std::span(std::span<const std::uint8_t>::const_iterator(current), input.cend()));

    return result;
}

auto Protecs::Networking::Packets::EntityComponentData::packedSize() const noexcept -> std::size_t
{
    std::size_t size = partialPackedSize();

    std::visit([&](const auto& component){
        size += component.packedSize();
    }, component);

    return size;
}


#define index_of(type) Wrecks::Utils::element_index_v<Protecs::Components::type, Protecs::Components::Variant>


static Protecs::Components::Variant deserializeComponent(std::size_t type, std::span<const std::uint8_t> input)
{
    const auto* current = input.data();

    switch (type) {
        case index_of(Level):       return Protecs::Components::Level::deserialize(current, input.size());
        case index_of(Movement):    return Protecs::Components::Movement::deserialize(current, input.size());
        case index_of(PathFinding): return Protecs::Components::PathFinding::deserialize(current, input.size());
        case index_of(PlayerInput): return Protecs::Components::PlayerInput::deserialize(current, input.size());
        case index_of(PlayerStats): return Protecs::Components::PlayerStats::deserialize(current, input.size());
        case index_of(Transform):   return Protecs::Components::Transform::deserialize(current, input.size());
        case index_of(Velocity):    return Protecs::Components::Velocity::deserialize(current, input.size());

        default: throw Protecs::SerializationError("unknown component type in entity component data packet");
    }
}
