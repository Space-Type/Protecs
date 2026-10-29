/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Unit tests for
** PlayerLeave packet
*/

#include <gtest/gtest.h>
#include <protecs.hpp>


using Protecs::Networking::Packets::PlayerLeave;


static constexpr PlayerLeave TEST_DATA = {};
static constexpr std::uint8_t SERIALIZED_TEST_DATA[1] = { '\0' };


TEST(networking_packets_PlayerLeave, packedSize)
{
    EXPECT_TRUE(TEST_DATA.packedSize() <= sizeof(TEST_DATA));
    EXPECT_TRUE(TEST_DATA.packedSize() == 0);
}

TEST(networking_packets_PlayerLeave, serialization)
{
    std::uint8_t buffer[100];

    EXPECT_NO_THROW(TEST_DATA.serialize(buffer));
    EXPECT_EQ(::memcmp(buffer, SERIALIZED_TEST_DATA, TEST_DATA.packedSize()), 0);
}

TEST(networking_packets_PlayerLeave, deserialization)
{
    PlayerLeave data;

    EXPECT_NO_THROW(data = PlayerLeave::deserialize(SERIALIZED_TEST_DATA));
}

TEST(networking_packets_PlayerLeave, serializeAndDeserialize)
{
    PlayerLeave initialData = {};
    PlayerLeave deserializedData;
    std::uint8_t buffer[100];

    EXPECT_NO_THROW(initialData.serialize(buffer));
    EXPECT_NO_THROW(deserializedData = PlayerLeave::deserialize(buffer));
}
