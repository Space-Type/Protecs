/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Unit tests for
** PlayerId packet
*/

#include <gtest/gtest.h>
#include <protecs.hpp>


using Protecs::Networking::Packets::PlayerId;


static constexpr PlayerId TEST_DATA = {
    .id = 751937,
};

static constexpr std::uint8_t SERIALIZED_TEST_DATA[] = {
    0x41, 0x79, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00,  // id
};


TEST(networking_packets_PlayerId, packedSize)
{
    EXPECT_TRUE(TEST_DATA.packedSize() <= sizeof(TEST_DATA));
    EXPECT_TRUE(TEST_DATA.packedSize() == sizeof(TEST_DATA.id));
}

TEST(networking_packets_PlayerId, serialization)
{
    std::uint8_t buffer[100];

    EXPECT_NO_THROW(TEST_DATA.serialize(buffer));
    EXPECT_EQ(::memcmp(buffer, SERIALIZED_TEST_DATA, TEST_DATA.packedSize()), 0);
}

TEST(networking_packets_PlayerId, deserialization)
{
    PlayerId data;

    EXPECT_NO_THROW(data = PlayerId::deserialize(SERIALIZED_TEST_DATA));

    EXPECT_EQ(data.id, TEST_DATA.id);
}

TEST(networking_packetes_PlayerId, serializeAndDeserialize)
{
    PlayerId initialData = { .id = 8734738157 };
    PlayerId deserializedData;
    std::uint8_t buffer[100];

    EXPECT_NO_THROW(initialData.serialize(buffer));
    EXPECT_NO_THROW(deserializedData = PlayerId::deserialize(buffer));

    EXPECT_EQ(initialData.id, deserializedData.id);
}

TEST(networking_packets_PlayerId, smallBufferSerialize)
{
    std::uint8_t buffer[1];

    EXPECT_THROW(TEST_DATA.serialize(buffer), Protecs::SerializationError);
}

TEST(networking_packets_PlayerId, smallBufferDeserialize)
{
    std::uint8_t buffer[1] = { 'c' };

    EXPECT_THROW(PlayerId::deserialize(buffer), Protecs::SerializationError);
}
