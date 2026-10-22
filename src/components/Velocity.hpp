/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** Velocity component
*/

#pragma once

#include <protecs/utils.hpp>


namespace Protecs::Components {
    struct Velocity {
        Utils::Vec2D<float> position;
        float angular;
    };
}
