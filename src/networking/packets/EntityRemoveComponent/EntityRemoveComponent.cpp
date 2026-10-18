/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Implementation for
** EntityRemoveComponent struct
*/

#include "EntityRemoveComponent.hpp"
#include <protecs/utils.hpp>


void Protecs::Networking::Packets::EntityRemoveComponent::serialize(std::span<std::uint8_t> output) const noexcept
{
    auto* current = output.data();

    Utils::copyFromValue(current, entity);
    Utils::copyFromValue(current, componentType);
}

auto Protecs::Networking::Packets::EntityRemoveComponent::deserialize(std::span<const std::uint8_t> output) noexcept -> EntityRemoveComponent
{
    const auto* current = output.data();
    EntityRemoveComponent result;

    Utils::copyToValue(result.entity, current);
    Utils::copyToValue(result.componentType, current);

    return result;
}
