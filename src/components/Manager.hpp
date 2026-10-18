/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** Component Manager type
*/

#pragma once

#include <protecs/components/types.hpp>
#include <wrecks/ecs.hpp>


namespace Protecs::Components {
    using Manager = Wrecks::ECS::ComponentManager<Transform,
                                                  Velocity>;
}
