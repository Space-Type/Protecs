/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** EntityAddComponent struct
*/

#pragma once

#include <protecs/common.hpp>
#include <cstdint>
#include <span>


namespace Protecs::Networking::Packets {
    struct EntityAddComponent {
        Entity entity;
        std::uint16_t componentType;

        void serialize(std::span<std::uint8_t> output) const noexcept;
        static EntityAddComponent deserialize(std::span<const std::uint8_t> input) noexcept;
    };
}
