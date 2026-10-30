/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Implementation for
** Movement system
*/

#include "Movement.hpp"


Protecs::Systems::Movement::Movement() noexcept
    : m_GetMovement()
    , m_GetVelocity()
{

}

void Protecs::Systems::Movement::operator()(Wrecks::ECS::Entity entity, Wrecks::DeltaTime dt)
{
    auto& movement = m_GetMovement(entity);
    auto& velocity = m_GetVelocity(entity);

    float speed = movement.speed * dt.count() / 16.666;
    velocity.position += movement.direction.normalized() * speed;
}
