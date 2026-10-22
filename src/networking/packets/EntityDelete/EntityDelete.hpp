/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** EntityDelete packet
*/

#pragma once

#include <protecs/common.hpp>
#include <cstdint>
#include <span>


namespace Protecs::Networking::Packets {
    struct EntityDelete {
        Entity id;

        void serialize(std::span<std::uint8_t> output) const;
        static EntityDelete deserialize(std::span<const std::uint8_t> input);

        [[nodiscard]] static constexpr std::size_t packedSize() noexcept { return sizeof(id); }
    };
}
