/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Unit tests for
** Packet class
*/

#include <gtest/gtest.h>
#include <protecs.hpp>
#include <variant>


using Protecs::Networking::Packet;
namespace Packets = Protecs::Networking::Packets;


TEST(networking_Packet, serializePing)
{
    Packet packet;
    Packets::Ping data;

    EXPECT_NO_THROW(packet = Packet::serialize(data));
    EXPECT_EQ(packet.filled, sizeof(std::uint8_t) + data.packedSize());
}

TEST(networking_Packet, deserializePing)
{
    Packet packet;
    Packets::PacketData data;

    packet.raw[0] = Wrecks::Utils::element_index_v<Packets::Ping, Packets::PacketData>;
    packet.filled = sizeof(std::uint8_t) + Packets::Ping::packedSize();

    EXPECT_NO_THROW(data = packet.deserialize());
    EXPECT_TRUE(std::holds_alternative<Packets::Ping>(data));
}

TEST(networking_Packet, invalidPacket)
{
    Packet packet;
    Packets::PacketData data;

    packet.raw[0] = 255;
    packet.filled = sizeof(std::uint8_t) + Packets::Ping::packedSize();

    EXPECT_THROW(packet.deserialize(), Protecs::SerializationError);
}

TEST(networking_Packet, printPing)
{
    Packet packet;

    packet.raw[0] = Wrecks::Utils::element_index_v<Packets::Ping, Packets::PacketData>;
    packet.filled = sizeof(std::uint8_t) + Packets::Ping::packedSize();

    std::stringstream stream;
    stream << packet << std::flush;

    EXPECT_EQ(stream.str(), "ping packet (1B)");
}

TEST(networking_Packet, printInvalidPacket)
{
    Packet packet;

    packet.raw[0] = 255;
    packet.filled = sizeof(std::uint8_t);

    std::stringstream stream;
    stream << packet << std::flush;

    EXPECT_EQ(stream.str(), "unknown packet (1B)");
}

TEST(networking_Packet, printEmptyPacket)
{
    Packet packet = {};

    std::stringstream stream;
    stream << packet << std::flush;

    EXPECT_EQ(stream.str(), "unknown packet (0B)");
}
