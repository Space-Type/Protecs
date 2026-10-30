/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** PlayerInput component
*/

#pragma once

#include <protecs/utils.hpp>


namespace Protecs::Components {
    struct PlayerInput {
        bool up;
        bool down;
        bool left;
        bool right;
        bool trigger;

        constexpr std::uint8_t packed() const noexcept
        {
            return
                (up      << 4) |
                (down    << 3) |
                (left    << 2) |
                (right   << 1) |
                (trigger << 0);
        }

        void serialize(std::uint8_t*& output, std::size_t size) const;
        static PlayerInput deserialize(const std::uint8_t*& data, std::size_t size);

        /**
         * Returns the size (in bytes) of the
         * struct, without taking into account
         * any padding / alignment bytes the
         * compiler may add to it.
         */
        [[nodiscard]] static constexpr std::size_t packedSize()
        {
            return sizeof(std::uint8_t);
        }
    };
}
