/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** EntityRemoveComponent struct
*/

#pragma once

#include <cstdint>
#include <span>


namespace Protecs::Networking::Packets {
    struct EntityRemoveComponent {
        std::uint32_t entity;
        std::uint16_t componentType;

        void serialize(std::span<std::uint8_t> output) const noexcept;
        static EntityRemoveComponent deserialize(std::span<const std::uint8_t> input) noexcept;
    };
}
