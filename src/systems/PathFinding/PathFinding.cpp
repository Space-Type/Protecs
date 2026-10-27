/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Implementation for
** PathFinding system
*/

#include "PathFinding.hpp"


static constexpr float VELOCITY_SNAP_DELTA = 0.00001;
static constexpr float sign(float value) noexcept;


Protecs::Systems::PathFinding::PathFinding() noexcept
    : m_GetPathFinding()
    , m_GetVelocity()
{

}

void Protecs::Systems::PathFinding::operator()(Wrecks::ECS::Entity entity, Wrecks::DeltaTime)
{
    auto& pathfinding = m_GetPathFinding(entity);
    auto& velocity  = m_GetVelocity(entity);

    switch (pathfinding.type) {
        case Components::PathFinding::STRAIGHT: return straightPathFinding(pathfinding, velocity);
        default: return;
    }
}

void Protecs::Systems::PathFinding::straightPathFinding(Components::PathFinding& pathfinding, Components::Velocity& velocity)
{
    if (velocity.position.x != pathfinding.targetVelocity.x) {
        velocity.position.x += pathfinding.acceleration * sign(pathfinding.targetVelocity.x - velocity.position.x);
        velocity.position.x = snapToDelta(velocity.position.x, pathfinding.targetVelocity.x);
    }

    if (velocity.position.y != pathfinding.targetVelocity.y) {
        velocity.position.y += pathfinding.acceleration * sign(pathfinding.targetVelocity.y);
        velocity.position.y = snapToDelta(velocity.position.y, pathfinding.targetVelocity.y);
    }
}

float Protecs::Systems::PathFinding::snapToDelta(float value, float target) noexcept
{
    return target - VELOCITY_SNAP_DELTA <= value && value <= target + VELOCITY_SNAP_DELTA
        ? target
        : value;
}

static constexpr float sign(float value) noexcept
{
    return (value > 0.0) - (value < 0.0);
}
