/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** Packet struct
*/

#pragma once

#include "../packets/PacketData.hpp"
#include <cstdint>
#include <array>


namespace Protecs::Networking {
    struct Packet {
        std::array<std::uint8_t, sizeof(Packets::PacketData)> raw;

        static Packet serialize(const Packets::PacketData& data);
        Packets::PacketData deserialize(std::size_t bytes) const;
    };
}
