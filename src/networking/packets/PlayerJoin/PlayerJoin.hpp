/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** PlayerJoin packet
*/

#pragma once

#include <string_view>
#include <cstdint>
#include <array>
#include <span>


namespace Protecs::Networking::Packets {
    /**
     * Asks the server if the sender
     * can join the game as a player.
     *
     * If successful, the server will
     * reply with a PlayerId packet.
     * Otherwise, a PlayerLeave packet
     * will be sent back.
     *
     * Sending a PlayerJoin packet as
     * a player who already joined has
     * no effect.
     */
    struct PlayerJoin {
        std::uint8_t length;
        std::array<char, 32> name;

        std::string_view str() const;

        void serialize(std::span<std::uint8_t> output) const;
        static PlayerJoin deserialize(std::span<const std::uint8_t> input);

        [[nodiscard]] constexpr std::size_t packedSize() const noexcept { return sizeof(length) + length; }
    };
}
