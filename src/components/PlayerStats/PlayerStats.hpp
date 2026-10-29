/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** PlayerStats component
*/

#pragma once

#include <cstdint>
#include <cstddef>


namespace Protecs::Components {
    /**
     * State of a player that clients
     * need to display (HUD, game over).
     *
     * It is set by the server on player
     * entities and synced like any other
     * shared component.
     */
    struct PlayerStats {
        std::uint8_t slot;    // 0-3, fixed while the player is connected
        std::uint8_t lives;   // 0 means the player is out of the game
        std::uint32_t score;

        void serialize(std::uint8_t*& output, std::size_t size) const;
        static PlayerStats deserialize(const std::uint8_t*& data, std::size_t size);

        /**
         * Returns the size (in bytes) of the
         * struct, without taking into account
         * any padding / alignment bytes the
         * compiler may add to it.
         */
        [[nodiscard]] static constexpr std::size_t packedSize()
        {
            return
                sizeof(slot) +
                sizeof(lives) +
                sizeof(score);
        }
    };
}
