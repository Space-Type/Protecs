/*
** EPITECH PROJECT, 2026
** Project - RType
** File description:
** Implementation for
** EntitySyncComponents
*/

#include "EntitySyncComponents.hpp"
#include <protecs/utils.hpp>


void Protecs::Networking::Packets::EntitySyncComponents::serialize(std::span<std::uint8_t> output) const noexcept
{
    auto* current = output.data();

    Utils::copyFromValue(current, entity);
    Utils::copyFromValue(current, signature);
}

auto Protecs::Networking::Packets::EntitySyncComponents::deserialize(std::span<const std::uint8_t> output) noexcept -> EntitySyncComponents
{
    const auto* current = output.data();
    EntitySyncComponents result;

    Utils::copyToValue(result.entity, current);
    Utils::copyToValue(result.signature, current);

    return result;
}
