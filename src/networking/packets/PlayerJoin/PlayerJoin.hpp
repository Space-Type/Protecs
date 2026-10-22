/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** PlayerJoin packet
*/

#pragma once

#include <cstdint>
#include <string>
#include <span>


namespace Protecs::Networking::Packets {
    struct PlayerJoin {
        std::uint8_t length;
        std::array<char, 32> name;

        std::string str() const;

        void serialize(std::span<std::uint8_t> output) const;
        static PlayerJoin deserialize(std::span<const std::uint8_t> input);

        [[nodiscard]] constexpr std::size_t packedSize() const noexcept { return sizeof(length) + length; }
    };
}
