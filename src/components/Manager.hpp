/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** Component Manager type
*/

#pragma once

#include <protecs/components/types.hpp>
#include <wrecks/utils.hpp>
#include <wrecks/ecs.hpp>
#include <variant>


namespace Protecs::Components {
    using Manager = Wrecks::ECS::ComponentManager<Level,
                                                  Movement,
                                                  PathFinding,
                                                  PlayerInput,
                                                  PlayerStats,
                                                  Transform,
                                                  Velocity>;

    using Variant = Wrecks::Utils::replace_container_type_t<std::variant<>, Manager>;
}
