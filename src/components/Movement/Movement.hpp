/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** Movement component
*/

#pragma once

#include <protecs/utils.hpp>


namespace Protecs::Components {
    struct Movement {
        Utils::Vec2D<float> position;
        float angular;

        void serialize(std::uint8_t*& output, std::size_t size) const;
        static Movement deserialize(const std::uint8_t*& data, std::size_t size);

        /**
         * Returns the size (in bytes) of the
         * struct, without taking into account
         * any padding / alignment bytes the
         * compiler may add to it.
         */
        [[nodiscard]] static constexpr std::size_t packedSize()
        {
            return
                sizeof(position.x) +
                sizeof(position.y) +
                sizeof(angular);
        }
    };
}
