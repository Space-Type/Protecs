/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Implementation for
** EntityRemoveComponent struct
*/

#include "EntityRemoveComponent.hpp"
#include <protecs/errors.hpp>
#include <protecs/utils.hpp>


void Protecs::Networking::Packets::EntityRemoveComponent::serialize(std::span<std::uint8_t> output) const
{
    if (output.size() < packedSize())
        throw SerializationError("unable to serialize EntityRemoveComponent packet as the output buffer is too small");

    auto* current = output.data();

    Utils::copyFromValue(current, entity);
    Utils::copyFromValue(current, componentType);
}

auto Protecs::Networking::Packets::EntityRemoveComponent::deserialize(std::span<const std::uint8_t> input) -> EntityRemoveComponent
{
    if (input.size() < packedSize())
        throw SerializationError("unable to deserialize EntityRemoveComponent packet as the input buffer is too small");

    const auto* current = input.data();
    EntityRemoveComponent result;

    Utils::copyToValue(result.entity, current);
    Utils::copyToValue(result.componentType, current);

    return result;
}
