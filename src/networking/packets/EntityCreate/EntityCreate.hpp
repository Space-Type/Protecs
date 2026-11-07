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
            PLAYER_MISSILE,  // shot by a player
            ENEMY_MISSILE,   // shot by an enemy
            PLAYER_BEAM_1,   // charged shot of a player, by charge level
            PLAYER_BEAM_2,
            PLAYER_BEAM_3,
            PLAYER_BEAM_4,
            PLAYER_BEAM_5,
            ENEMY_DOBKERATOPS,       // stage 1 boss: its body, which only absorbs shots
            ENEMY_DOBKERATOPS_CORE,  // its weak point, the only part that takes damage
        };

        static constexpr std::uint8_t sequence = 0;

        Tick simulationTick;
        NetworkEntity id;
        EntityType type;

        void serialize(std::span<std::uint8_t> output) const;
        static EntityCreate deserialize(std::span<const std::uint8_t> input);

        [[nodiscard]] static constexpr std::size_t packedSize() noexcept { return sizeof(simulationTick) + sizeof(id) + sizeof(type); }
        [[nodiscard]] static constexpr std::string_view packetName() noexcept { return "entity-create"; }
    };
}
