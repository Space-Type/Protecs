/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Implementation for
** EntityCreate packet
*/

#include "EntityCreate.hpp"
#include <protecs/errors.hpp>
#include <protecs/utils.hpp>


void Protecs::Networking::Packets::EntityCreate::serialize(std::span<std::uint8_t> output) const
{
    if (output.size() < packedSize())
        throw SerializationError("unable to serialize EntityCreate packet as the output buffer is too small");

    auto* current = output.data();

    Utils::copyFromValue(current, id);
    Utils::copyFromValue(current, type);
}

auto Protecs::Networking::Packets::EntityCreate::deserialize(std::span<const std::uint8_t> input) -> EntityCreate
{
    if (input.size() < packedSize())
        throw SerializationError("unable to deserialize EntityCreate packet as the input buffer is too small");

    const auto* current = input.data();

    EntityCreate result;
    Utils::copyToValue(result.id, current);
    Utils::copyToValue(result.type, current);
    return result;
}
