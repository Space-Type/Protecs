/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** Ping packet
*/

#pragma once

#include <cstdint>
#include <span>


namespace Protecs::Networking::Packets {
    /**
     * The Ping packet is usually sent
     * by the server to determine if
     * a client is still connected.
     *
     * If a client receives a ping,
     * it should reply with a ping
     * of its own, lest it will be
     * marked as disconnected and
     * thus leave the game.
     */
    struct Ping {
        constexpr static void serialize(std::span<std::uint8_t> output) {}
        constexpr static Ping deserialize(std::span<const std::uint8_t> input) noexcept { return Ping{}; }

        [[nodiscard]] static constexpr std::size_t packedSize() noexcept { return 0; }
    };
}
