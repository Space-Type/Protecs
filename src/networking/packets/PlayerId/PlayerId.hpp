/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** PlayerId packet
*/

#pragma once

#include <protecs/common.hpp>
#include <cstdint>
#include <span>


namespace Protecs::Networking::Packets {
    /**
     * Packet that tells a client
     * which entity their inputs
     * control (i.e. which entity
     * the player is).
     *
     * It is sent to the client after
     * the server receives and approves
     * a PlayerJoin packet.
     */
    struct PlayerId {
        NetworkEntity id;

        void serialize(std::span<std::uint8_t> output) const;
        static PlayerId deserialize(std::span<const std::uint8_t> input);

        [[nodiscard]] static constexpr std::size_t packedSize() noexcept { return sizeof(id); }
    };
}
