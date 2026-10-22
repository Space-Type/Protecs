/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Implementation for
** PlayerInput packet
*/

#include "PlayerInput.hpp"
#include <protecs/errors.hpp>
#include <protecs/utils.hpp>


void Protecs::Networking::Packets::PlayerInput::serialize(std::span<std::uint8_t> output) const
{
    if (output.size() < packedSize())
        throw SerializationError("unable to serialize PlayerInput packet as the output buffer is too small");

    auto* current = output.data();

    Utils::copyFromValue(current, input);
    Utils::copyFromValue(current, state);
}

auto Protecs::Networking::Packets::PlayerInput::deserialize(std::span<const std::uint8_t> input) -> PlayerInput
{
    if (input.size() < packedSize())
        throw SerializationError("unable to deserialize PlayerInput packet as the input buffer is too small");

    const auto* current = input.data();
    PlayerInput result;

    Utils::copyToValue(result.input, current);
    Utils::copyToValue(result.state, current);

    return result;
}
