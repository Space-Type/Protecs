/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** PlayerLeave packet
*/

#pragma once

#include <cstdint>
#include <span>


namespace Protecs::Networking::Packets {
    /**
     * Packet that should be sent
     * to the server when the player
     * leaves the game.
     *
     * Failure to send this will make
     * the client timeout and thus leave,
     * but only after a delay and with a
     * less descriptive message, so clients
     * should send this packet when the
     * player leaves the game.
     *
     * In the event that a client disconnects
     * without sending this packet, the server
     * will send a PlayerLeave of its own when
     * the timeout is reached (i.e. when a ping
     * isn't replied to), such that the client
     * knows the player got disconnected from the
     * game.
     */
    struct PlayerLeave {
        constexpr static void serialize(std::span<std::uint8_t> output) {}
        constexpr static PlayerLeave deserialize(std::span<const std::uint8_t> input) noexcept { return PlayerLeave{}; }

        [[nodiscard]] constexpr std::size_t packedSize() const noexcept { return 0; }
    };
}
