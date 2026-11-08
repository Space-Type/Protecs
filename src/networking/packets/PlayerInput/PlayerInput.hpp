/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** PlayerInput packet
*/

#pragma once

#include <protecs/common.hpp>
#include <string_view>
#include <cstdint>
#include <span>


namespace Protecs::Networking::Packets {
    struct PlayerInput {
        Tick simulationTick;
        std::uint8_t sequence;  // relative to specified simulation tick
        enum : std::uint8_t { UP, DOWN, LEFT, RIGHT, TRIGGER, FORCE } input;  // a receiver ignores a value it does not know
        enum : std::uint8_t { HOLD_DOWN, RELEASE } state;

        void serialize(std::span<std::uint8_t> output) const;
        static PlayerInput deserialize(std::span<const std::uint8_t> input);

        [[nodiscard]] static constexpr std::size_t packedSize() noexcept { return sizeof(simulationTick) + sizeof(sequence) + sizeof(input) + sizeof(state); }
        [[nodiscard]] static constexpr std::string_view packetName() noexcept { return "player-input"; }
    };
}
