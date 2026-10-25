/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Implementation for
** EntityAddComponent struct
*/

#include "EntityAddComponent.hpp"
#include <protecs/errors.hpp>
#include <protecs/utils.hpp>


void Protecs::Networking::Packets::EntityAddComponent::serialize(std::span<std::uint8_t> output) const
{
    if (output.size() < packedSize())
        throw SerializationError("unable to serialize EntityAddComponent packet as the output buffer is too small");

    auto* current = output.data();

    Utils::copyFromValue(current, entity);
    Utils::copyFromValue(current, type);
}

auto Protecs::Networking::Packets::EntityAddComponent::deserialize(std::span<const std::uint8_t> input) -> EntityAddComponent
{
    if (input.size() < packedSize())
        throw SerializationError("unable to deserialize EntityAddComponent packet as the input buffer is too small");

    const auto* current = input.data();
    EntityAddComponent result;

    Utils::copyToValue(result.entity, current);
    Utils::copyToValue(result.type, current);

    return result;
}
