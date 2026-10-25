/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Implementation for
** Motion system
*/

#include "Motion.hpp"


static constexpr float FRICTION_FACTOR_X = 0.90;
static constexpr float FRICTION_FACTOR_Y = FRICTION_FACTOR_X;
static constexpr Protecs::Utils::Vec2D<float> POSITION_MIN = { 0.f, 0.f };
static constexpr Protecs::Utils::Vec2D<float> POSITION_MAX = { Protecs::POSITION_MAX_X, Protecs::POSITION_MAX_Y };


Protecs::Systems::Motion::Motion() noexcept
    : m_GetTransform()
    , m_GetVelocity()
{

}

void Protecs::Systems::Motion::operator()(Wrecks::ECS::Entity entity, Wrecks::DeltaTime)
{
    auto& transform = m_GetTransform(entity);
    auto& velocity = m_GetVelocity(entity);

    transform.position += velocity.position;
    transform.position.clamp(POSITION_MIN, POSITION_MAX);

    velocity.position.x *= FRICTION_FACTOR_X;
    velocity.position.y *= FRICTION_FACTOR_Y;
}
