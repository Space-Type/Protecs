/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Implementation for
** Motion system
*/

#include "Motion.hpp"
#include <algorithm>


static constexpr float FRICTION_FACTOR_X = 0.90;
static constexpr float FRICTION_FACTOR_Y = FRICTION_FACTOR_X;


Protecs::Systems::Motion::Motion() noexcept
    : m_GetTransform()
    , m_GetVelocity()
{

}

void Protecs::Systems::Motion::operator()(Wrecks::ECS::Entity entity)
{
    auto& velocity = m_GetTransform(entity);
    auto& transform = m_GetVelocity(entity);

    transform.position += velocity.position;

    transform.position.x = std::clamp(transform.position.x, 0.f, POSITION_MAX_X);
    transform.position.y = std::clamp(transform.position.y, 0.f, POSITION_MAX_Y);

    velocity.position.x *= FRICTION_FACTOR_X;
    velocity.position.y *= FRICTION_FACTOR_Y;
}
