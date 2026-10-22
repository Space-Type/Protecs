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
    struct Ping {
        constexpr static void serialize(std::span<std::uint8_t> output) {}
        constexpr static Ping deserialize(std::span<const std::uint8_t> input) noexcept { return Ping{}; }

        [[nodiscard]] constexpr std::size_t packedSize() const noexcept { return 0; }
    };
}
