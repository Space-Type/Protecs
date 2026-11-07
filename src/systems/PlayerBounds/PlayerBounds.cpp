/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Implementation for
** PlayerBounds system
*/

#include "PlayerBounds.hpp"
#include <protecs/common.hpp>


Protecs::Systems::PlayerBounds::PlayerBounds() noexcept
    : m_GetTransform()
{

}

void Protecs::Systems::PlayerBounds::operator()(Wrecks::ECS::Entity entity, Wrecks::DeltaTime dt)
{
    auto& transform = m_GetTransform(entity);

    transform.position.clamp(Utils::Vec2D{ 0.f, 0.f }, Utils::Vec2D{ MAP_MAX_X, MAP_MAX_Y });
}
