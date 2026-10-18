/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Implementation for
** EntityAddComponent struct
*/

#include "EntityAddComponent.hpp"
#include <protecs/utils.hpp>


void Protecs::Networking::Packets::EntityAddComponent::serialize(std::span<std::uint8_t> output) const noexcept
{
    auto* current = output.data();

    Utils::copyFromValue(current, entity);
    Utils::copyFromValue(current, componentType);
}

auto Protecs::Networking::Packets::EntityAddComponent::deserialize(std::span<const std::uint8_t> output) noexcept -> EntityAddComponent
{
    const auto* current = output.data();
    EntityAddComponent result;

    Utils::copyToValue(result.entity, current);
    Utils::copyToValue(result.componentType, current);

    return result;
}
