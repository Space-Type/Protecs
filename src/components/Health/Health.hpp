/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** Health component
*/

#pragma once

#include <cstdint>
#include <cstddef>


namespace Protecs::Components {
    /**
     * Hit points of an enemy (or a boss). The server
     * decides the damage; clients can show a hit, or
     * the health of a boss.
     */
    struct Health {
        std::uint16_t hp;
        std::uint16_t max;

        void serialize(std::uint8_t*& output, std::size_t size) const;
        static Health deserialize(const std::uint8_t*& data, std::size_t size);

        /**
         * Returns the size (in bytes) of the
         * struct, without taking into account
         * any padding / alignment bytes the
         * compiler may add to it.
         */
        [[nodiscard]] static constexpr std::size_t packedSize()
        {
            return
                sizeof(hp) +
                sizeof(max);
        }
    };
}
