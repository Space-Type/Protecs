/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Implementation for
** EntityPosition struct
*/

#include "EntityPosition.hpp"
#include <protecs/utils.hpp>


void Protecs::Networking::Packets::EntityPosition::serialize(std::span<std::uint8_t> output) const noexcept
{
    auto* current = output.data();

    Utils::copyFromValue(current, entity);
    Utils::copyFromValue(current, x);
    Utils::copyFromValue(current, y);
}

auto Protecs::Networking::Packets::EntityPosition::deserialize(std::span<const std::uint8_t> output) noexcept -> EntityPosition
{
    const auto* current = output.data();
    EntityPosition result;

    Utils::copyToValue(result.entity, current);
    Utils::copyToValue(result.x, current);
    Utils::copyToValue(result.y, current);

    return result;
}
