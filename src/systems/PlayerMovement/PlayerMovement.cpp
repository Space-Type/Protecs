/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Implementation for
** PlayerMovement system
*/

#include "PlayerMovement.hpp"


Protecs::Systems::PlayerMovement::PlayerMovement() noexcept
    : m_GetPlayerInput()
    , m_GetMovement()
{

}

void Protecs::Systems::PlayerMovement::operator()(Wrecks::ECS::Entity entity, Wrecks::DeltaTime dt)
{
    auto& input = m_GetPlayerInput(entity);
    auto& movement = m_GetMovement(entity);

    movement.direction.x = input.right - input.left;
    movement.direction.y = input.down - input.up;
}
