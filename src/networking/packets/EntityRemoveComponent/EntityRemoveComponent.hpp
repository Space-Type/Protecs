/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** EntityRemoveComponent struct
*/

#pragma once

#include <protecs/common.hpp>
#include <cstdint>
#include <span>


namespace Protecs::Networking::Packets {
    struct EntityRemoveComponent {
        Entity entity;
        std::uint16_t componentType;

        void serialize(std::span<std::uint8_t> output) const;
        static EntityRemoveComponent deserialize(std::span<const std::uint8_t> input);

        [[nodiscard]] static constexpr std::size_t packedSize() noexcept { return sizeof(entity) + sizeof(componentType); }
    };
}
