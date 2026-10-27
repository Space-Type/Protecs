/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Unit tests for
** PathFinding system
*/

#include <gtest/gtest.h>
#include <protecs.hpp>
#include <wrecks.hpp>


using Engine = Wrecks::ECS::Engine<Protecs::Systems::Tuple, Protecs::Components::Manager>;
using PathFindingType = typename Protecs::Components::PathFinding::PathFindingType;


TEST(systems_PathFinding, systemWorks)
{
    Engine engine;
    auto entity = engine.createEntity();

    engine.addComponent(entity, Protecs::Components::PathFinding{ .type = PathFindingType::STRAIGHT, .targetVelocity = { 3.f, 2.f }, .acceleration = 10.f });
    engine.addComponent(entity, Protecs::Components::Velocity{});

    engine.fixedUpdate(Wrecks::DeltaTime(0));
}

TEST(systems_PathFinding, invalidPathfindingType)
{
    Engine engine;
    auto entity = engine.createEntity();

    engine.addComponent(entity, Protecs::Components::PathFinding{ .type = static_cast<PathFindingType>(3) });
    engine.addComponent(entity, Protecs::Components::Velocity{});

    engine.fixedUpdate(Wrecks::DeltaTime(0));
}
