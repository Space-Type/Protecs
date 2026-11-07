/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** PlayerName component
*/

#pragma once

#include <array>
#include <cstdint>
#include <cstddef>
#include <string_view>


namespace Protecs::Components {
    /**
     * Nickname of a player, as sent in its
     * PlayerJoin packet, so that clients can
     * show it (e.g. above the player's ship).
     *
     * It is set by the server on player
     * entities and synced like any other
     * shared component.
     */
    struct PlayerName {
        static constexpr std::size_t MAX_LENGTH = 32;  // Same as PlayerJoin

        std::uint8_t length = 0;
        std::array<char, MAX_LENGTH> name = {};

        // Names longer than MAX_LENGTH are truncated
        static PlayerName fromStr(std::string_view name);
        std::string_view str() const;

        void serialize(std::uint8_t*& output, std::size_t size) const;

        // Throws if the buffer is too small or the length is above MAX_LENGTH
        static PlayerName deserialize(const std::uint8_t*& data, std::size_t size);

        /**
         * Returns the size (in bytes) of the
         * struct, without taking into account
         * any padding / alignment bytes the
         * compiler may add to it.
         */
        [[nodiscard]] constexpr std::size_t packedSize() const noexcept { return sizeof(length) + length; }
    };
}
