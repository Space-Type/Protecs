/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** EntityPosition struct
*/

#pragma once

#include <cstdint>
#include <span>


namespace Protecs::Networking::Packets {
    struct EntityPosition {
        std::uint32_t entity;
        float x;
        float y;

        void serialize(std::span<std::uint8_t> output) const noexcept;
        static EntityPosition deserialize(std::span<const std::uint8_t> input) noexcept;
    };
}
