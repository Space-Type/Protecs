/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Unit tests for
** Movement system
*/

#include <gtest/gtest.h>
#include <protecs.hpp>
#include <wrecks.hpp>


using Engine = Wrecks::ECS::Engine<Protecs::Systems::Tuple, Protecs::Components::Manager>;


TEST(systems_Movement, systemWorks)
{
    Engine engine;
    auto entity = engine.createEntity();

    engine.addComponent(entity, Protecs::Components::Movement{});
    engine.addComponent(entity, Protecs::Components::Velocity{});

    engine.fixedUpdate(Wrecks::DeltaTime(0));
}
