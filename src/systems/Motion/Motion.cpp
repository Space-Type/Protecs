/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Implementation for
** Motion system
*/

#include "Motion.hpp"


static constexpr float FRICTION_FACTOR_X = 0.89f;
static constexpr float FRICTION_FACTOR_Y = FRICTION_FACTOR_X;


Protecs::Systems::Motion::Motion() noexcept
{

}

void Protecs::Systems::Motion::operator()(Wrecks::ECS::Entity entity)
{
    // Game::Engine& engine = *reinterpret_cast<Game::Engine*>(m_Engine);

    // auto& physicsState = engine.get<Components::Physics>()[entity];
    // auto& transforms = engine.get<Components::Transform>()[entity];

    // physicsState.velocityX += 3.f * (IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT));
    // physicsState.velocityY += 3.f * (IsKeyDown(KEY_DOWN) - IsKeyDown(KEY_UP));

    // physicsState.velocityX = std::clamp(physicsState.velocityX, -2.f, 2.f);
    // physicsState.velocityY = std::clamp(physicsState.velocityY, -2.f, 2.f);

    // transforms.x += physicsState.velocityX;
    // transforms.y += physicsState.velocityY;

    // physicsState.velocityX *= FRICTION_FACTOR_X;
    // physicsState.velocityY *= FRICTION_FACTOR_Y;
}
