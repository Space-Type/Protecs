/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Implementation for
** EntityDelete packet
*/

#include "EntityDelete.hpp"
#include <protecs/errors.hpp>
#include <protecs/utils.hpp>


void Protecs::Networking::Packets::EntityDelete::serialize(std::span<std::uint8_t> output) const
{
    if (output.size() < packedSize())
        throw SerializationError("unable to serialize EntityDelete packet as the output buffer is too small");

    auto* current = output.data();

    Utils::copyFromValue(current, id);
}

auto Protecs::Networking::Packets::EntityDelete::deserialize(std::span<const std::uint8_t> input) -> EntityDelete
{
    if (input.size() < packedSize())
        throw SerializationError("unable to deserialize EntityDelete packet as the input buffer is too small");

    const auto* current = input.data();

    EntityDelete result;
    Utils::copyToValue(result.id, current);
    return result;
}
