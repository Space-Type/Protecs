/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Implementation for
** Motion system
*/

#include "Motion.hpp"


static constexpr float FRICTION_FACTOR_X = 0.95;
static constexpr float FRICTION_FACTOR_Y = FRICTION_FACTOR_X;
static constexpr float MIN_VELOCITY = 0.0005f;  // at this velocity, the velocity turns 0.0


Protecs::Systems::Motion::Motion() noexcept
    : m_GetTransform()
    , m_GetVelocity()
{

}

void Protecs::Systems::Motion::operator()(Wrecks::ECS::Entity entity, Wrecks::DeltaTime)
{
    auto& transform = m_GetTransform(entity);
    auto& velocity  = m_GetVelocity(entity);

    transform.position += velocity.position;

    velocity.position.x *= FRICTION_FACTOR_X;
    velocity.position.y *= FRICTION_FACTOR_Y;

    velocity.position.x = std::abs(velocity.position.x) < MIN_VELOCITY ? 0.f : velocity.position.x;
    velocity.position.y = std::abs(velocity.position.y) < MIN_VELOCITY ? 0.f : velocity.position.y;
}
