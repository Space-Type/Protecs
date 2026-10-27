/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** EntityList packet
*/

#pragma once

#include <protecs/common.hpp>
#include <vector>
#include <span>


namespace Protecs::Networking::Packets {
    struct EntityList {
        std::vector<std::pair<NetworkEntity, Signature>> entities;

        void serialize(std::span<std::uint8_t> output) const;
        static EntityList deserialize(std::span<const std::uint8_t> input);

        [[nodiscard]] static constexpr std::size_t partialPackedSize() noexcept { return sizeof(std::uint32_t); }
        [[nodiscard]] std::size_t packedSize() const noexcept;
    };
}
