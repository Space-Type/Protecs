/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Implementation for
** PlayerId packet
*/

#include "PlayerId.hpp"
#include <protecs/errors.hpp>
#include <protecs/utils.hpp>


void Protecs::Networking::Packets::PlayerId::serialize(std::span<std::uint8_t> output) const
{
    if (output.size() < packedSize())
        throw SerializationError("unable to serialize PlayerId packet as the output buffer is too small");

    auto* current = output.data();

    Utils::copyFromValue(current, id);
}

auto Protecs::Networking::Packets::PlayerId::deserialize(std::span<const std::uint8_t> input) -> PlayerId
{
    if (input.size() < packedSize())
        throw SerializationError("unable to deserialize PlayerId packet as the input buffer is too small");

    const auto* current = input.data();
    PlayerId result;

    Utils::copyToValue(result.id, current);

    return result;
}
