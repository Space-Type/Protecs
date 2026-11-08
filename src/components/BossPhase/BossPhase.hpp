/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** BossPhase component
*/

#pragma once

#include <cstdint>
#include <cstddef>


namespace Protecs::Components {
    /**
     * Phase of a boss, on its weak point: 1 when it comes,
     * then higher as it gets angrier. Clients show the change
     * (flash, sound and text).
     */
    struct BossPhase {
        std::uint8_t phase = 1;

        void serialize(std::uint8_t*& output, std::size_t size) const;
        static BossPhase deserialize(const std::uint8_t*& data, std::size_t size);

        /**
         * Returns the size (in bytes) of the
         * struct, without taking into account
         * any padding / alignment bytes the
         * compiler may add to it.
         */
        [[nodiscard]] static constexpr std::size_t packedSize()
        {
            return sizeof(phase);
        }
    };
}
