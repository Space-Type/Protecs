/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** EntityCreate packet
*/

#pragma once

#include <protecs/common.hpp>
#include <cstdint>
#include <span>


namespace Protecs::Networking::Packets {
    struct EntityCreate {
        enum EntityType : std::uint8_t {
            GENERIC = 0,
            PLAYER,
            ENEMY_PATA_PATA,
            ENEMY_SCANT,
        };

        NetworkEntity id;
        EntityType type;

        void serialize(std::span<std::uint8_t> output) const;
        static EntityCreate deserialize(std::span<const std::uint8_t> input);

        [[nodiscard]] static constexpr std::size_t packedSize() noexcept { return sizeof(id) + sizeof(type); }
    };
}
