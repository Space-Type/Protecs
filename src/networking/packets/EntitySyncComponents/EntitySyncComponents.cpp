/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Implementation for
** EntitySyncComponents struct
*/

#include "EntitySyncComponents.hpp"
#include <protecs/errors.hpp>
#include <protecs/utils.hpp>


void Protecs::Networking::Packets::EntitySyncComponents::serialize(std::span<std::uint8_t> output) const
{
    if (output.size() < packedSize())
        throw SerializationError("unable to serialize EntitySyncComponents packet as the output buffer is too small");

    auto* current = output.data();

    Utils::copyFromValue(current, entity);
    Utils::copyFromValue(current, signature);
}

auto Protecs::Networking::Packets::EntitySyncComponents::deserialize(std::span<const std::uint8_t> input) -> EntitySyncComponents
{
    if (input.size() < packedSize())
        throw SerializationError("unable to deserialize EntitySyncComponents packet as the input buffer is too small");

    const auto* current = input.data();
    EntitySyncComponents result;

    Utils::copyToValue(result.entity, current);
    Utils::copyToValue(result.signature, current);

    return result;
}
