/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** TickSync packet
*/

#pragma once

#include <protecs/common.hpp>
#include <string_view>
#include <cstdint>
#include <chrono>
#include <span>


namespace Protecs::Networking::Packets {
    struct TickSync {
        Protecs::Tick clientTick;
        Protecs::Tick serverTick;
        std::chrono::steady_clock::time_point serverTime;

        void serialize(std::span<std::uint8_t> output) const;
        static TickSync deserialize(std::span<const std::uint8_t> input);

        [[nodiscard]] static constexpr std::size_t packedSize() noexcept { return sizeof(clientTick) + sizeof(serverTick) + sizeof(serverTime.time_since_epoch()); }
        [[nodiscard]] static constexpr std::string_view packetName() noexcept { return "tick-sync"; }
    };
}
