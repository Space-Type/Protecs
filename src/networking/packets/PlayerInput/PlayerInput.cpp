/*
** EPITECH PROJECT, 2026
** Project - RType
** File description:
** Implementation for
** PlayerInput struct
*/

#include "PlayerInput.hpp"
#include <protecs/utils.hpp>


void Protecs::Networking::Packets::PlayerInput::serialize(std::span<std::uint8_t> output) const noexcept
{
    auto* current = output.data();

    Utils::copyFromValue(current, input);
    Utils::copyFromValue(current, state);
}

auto Protecs::Networking::Packets::PlayerInput::deserialize(std::span<const std::uint8_t> output) noexcept -> PlayerInput
{
    const auto* current = output.data();
    PlayerInput result;

    Utils::copyToValue(result.input, current);
    Utils::copyToValue(result.state, current);

    return result;
}
