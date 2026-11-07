/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Unit tests for
** PlayerJoin packet
*/

#include <gtest/gtest.h>
#include <protecs.hpp>


using Protecs::Networking::Packets::PlayerJoin;


static constexpr PlayerJoin TEST_DATA = {
    .length = 4,
    .name = { "John" },
};

static constexpr std::uint8_t SERIALIZED_TEST_DATA[] = {
    0x04,                // length
    'J', 'o', 'h', 'n',  // name
};


TEST(networking_packets_PlayerJoin, packedSize)
{
    EXPECT_EQ(TEST_DATA.str().length(), TEST_DATA.length);
    EXPECT_EQ(TEST_DATA.packedSize(), sizeof(TEST_DATA.length) + TEST_DATA.length * sizeof(char));
}

TEST(networking_packets_PlayerJoin, serialization)
{
    std::uint8_t buffer[100];

    EXPECT_NO_THROW(TEST_DATA.serialize(buffer));
    EXPECT_EQ(::memcmp(buffer, SERIALIZED_TEST_DATA, TEST_DATA.packedSize()), 0);
}

TEST(networking_packets_PlayerJoin, deserialization)
{
    PlayerJoin data;

    EXPECT_NO_THROW(data = PlayerJoin::deserialize(SERIALIZED_TEST_DATA));

    EXPECT_EQ(data.length, TEST_DATA.length);
    EXPECT_EQ(::memcmp(data.name.data(), TEST_DATA.name.data(), data.length), 0);
}

TEST(networking_packets_PlayerJoin, serializeAndDeserialize)
{
    PlayerJoin initialData = PlayerJoin::fromStr("Halberd");
    PlayerJoin deserializedData;
    std::uint8_t buffer[100];

    EXPECT_NO_THROW(initialData.serialize(buffer));
    EXPECT_NO_THROW(deserializedData = PlayerJoin::deserialize(buffer));

    EXPECT_EQ(initialData.length, deserializedData.length);
    EXPECT_EQ(::memcmp(initialData.name.data(), deserializedData.name.data(), initialData.length), 0);
}

TEST(networking_packets_PlayerJoin, smallBufferSerialize)
{
    std::uint8_t buffer[1];

    EXPECT_THROW(TEST_DATA.serialize(buffer), Protecs::SerializationError);
}

TEST(networking_packets_PlayerJoin, smallBufferDeserialize)
{
    std::span<std::uint8_t> buffer1;
    std::uint8_t buffer2[1] = { 'c' };

    EXPECT_THROW(PlayerJoin::deserialize(buffer1), Protecs::SerializationError);
    EXPECT_THROW(PlayerJoin::deserialize(buffer2), Protecs::SerializationError);
}

TEST(networking_packets_PlayerJoin, tooLongNameDeserialize)
{
    std::uint8_t buffer[300] = {};

    buffer[0] = 33;
    EXPECT_THROW(PlayerJoin::deserialize(buffer), Protecs::SerializationError);
    buffer[0] = 255;
    EXPECT_THROW(PlayerJoin::deserialize(buffer), Protecs::SerializationError);
}

TEST(networking_packets_PlayerJoin, truncatedNameDeserialize)
{
    // A valid length, but fewer name bytes than announced
    std::uint8_t buffer[6] = { 10, 'J', 'o', 'h', 'n', '!' };

    EXPECT_THROW(PlayerJoin::deserialize(buffer), Protecs::SerializationError);
}

TEST(networking_packets_PlayerJoin, longestNameDeserialize)
{
    std::uint8_t buffer[33] = {};

    buffer[0] = 32;
    EXPECT_NO_THROW(PlayerJoin::deserialize(buffer));
}

TEST(networking_packets_PlayerJoin, tooLongNameSerialize)
{
    PlayerJoin data = PlayerJoin::fromStr("John");
    std::uint8_t buffer[300];

    data.length = 33;
    EXPECT_THROW(data.serialize(buffer), Protecs::SerializationError);
}

TEST(networking_packets_PlayerJoin, packetName)
{
    EXPECT_EQ(PlayerJoin::packetName(), "player-join");
}
