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
        NetworkEntity entity;
        ComponentType type;

        void serialize(std::span<std::uint8_t> output) const;
        static EntityAddComponent deserialize(std::span<const std::uint8_t> input);

        static constexpr std::size_t packedSize() noexcept { return sizeof(entity) + sizeof(type); }
    };
}
