/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** Common utilities
*/

#pragma once

#include <wrecks/common.hpp>
#include <wrecks/ecs.hpp>


namespace Protecs {
    using NetworkEntity = std::uint64_t;
    using Signature = Wrecks::Signature;

    inline constexpr float POSITION_MAX_X = 800.f;
    inline constexpr float POSITION_MAX_Y = 450.f;
}
