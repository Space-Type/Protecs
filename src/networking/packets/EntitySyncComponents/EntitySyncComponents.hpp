/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** EntitySyncComponents struct
*/

#pragma once

#include <protecs/common.hpp>
#include <cstdint>
#include <span>


namespace Protecs::Networking::Packets {
    /**
     * Request from the client to
     * synchronize an entity's components.
     *
     * If the server received the packet,
     * it will reciprocate with the same
     * packet with the server's data
     * (i.e. if the signature is different,
     * the server's signature will be sent
     * instead).
     *
     * If the signature is out of date, the
     * server will automatically send the
     * difference in components to the client,
     * via the EntityAddComponent and
     * EntityRemoveComponent packets.
     */
    struct EntitySyncComponents {
        NetworkEntity entity;
        Signature signature;

        void serialize(std::span<std::uint8_t> output) const;
        static EntitySyncComponents deserialize(std::span<const std::uint8_t> input);

        [[nodiscard]] static constexpr std::size_t packedSize() noexcept { return sizeof(entity) + (Signature{}.size() + 7) / 8; }
    };
}
