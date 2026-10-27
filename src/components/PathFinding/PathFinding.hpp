/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** PathFinding component
*/

#pragma once

#include <protecs/utils.hpp>
#include <cstdint>
#include <cstddef>


namespace Protecs::Components {
    struct PathFinding {
        enum PathFindingType : std::uint8_t {
            STRAIGHT = 0,
        };

        PathFindingType type;
        Utils::Vec2D<float> targetVelocity;
        float acceleration;

        void serialize(std::uint8_t*& output, std::size_t size) const;
        static PathFinding deserialize(const std::uint8_t*& data, std::size_t size);

        /**
         * Returns the size (in bytes) of the
         * struct, without taking into account
         * any padding / alignment bytes the
         * compiler may add to it.
         */
        [[nodiscard]] static constexpr std::size_t packedSize()
        {
            return
                sizeof(type) +
                sizeof(targetVelocity.x) +
                sizeof(targetVelocity.y) +
                sizeof(acceleration);
        }
    };
}
