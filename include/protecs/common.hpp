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
    using ComponentType = std::uint16_t;
    using Signature = Wrecks::Signature;
    using Tick = std::uint32_t;

    inline constexpr float MAP_MAX_X = 800.f;
    inline constexpr float MAP_MAX_Y = 450.f;

    inline constexpr float PLAYER_WIDTH = 34.f;
    inline constexpr float PLAYER_HEIGHT = 17.f;

    inline constexpr Wrecks::DeltaTime FIXED_UPDATE_RATE = std::chrono::duration<double>(1.0 / 120.0);
}
