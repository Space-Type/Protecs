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

    inline constexpr float POSITION_MAX_X = 800.f;
    inline constexpr float POSITION_MAX_Y = 450.f;
}
