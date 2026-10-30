/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Unit tests for
** PlayerMovement system
*/

#include <gtest/gtest.h>
#include <protecs.hpp>
#include <wrecks.hpp>


using Engine = Wrecks::ECS::Engine<Protecs::Systems::Tuple, Protecs::Components::Manager>;


TEST(systems_PlayerMovement, systemWorks)
{
    Engine engine;
    auto entity = engine.createEntity();

    engine.addComponent(entity, Protecs::Components::PlayerInput{});
    engine.addComponent(entity, Protecs::Components::Movement{});

    engine.fixedUpdate(Wrecks::DeltaTime(0));
}
