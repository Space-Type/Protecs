/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Unit tests for
** EntityDelete packet
*/

#include <gtest/gtest.h>
#include <protecs.hpp>


using Protecs::Networking::Packets::EntityDelete;


static constexpr EntityDelete TEST_DATA = {
    .id   = 751937,
};

static constexpr std::uint8_t SERIALIZED_TEST_DATA[] = {
    0x41, 0x79, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00,  // id
};


TEST(networking_packets_EntityDelete, packedSize)
{
    EXPECT_LE(TEST_DATA.packedSize(), sizeof(TEST_DATA));
    EXPECT_EQ(TEST_DATA.packedSize(), sizeof(TEST_DATA.id));
}

TEST(networking_packets_EntityDelete, serialization)
{
    std::uint8_t buffer[100];

    EXPECT_NO_THROW(TEST_DATA.serialize(buffer));
    EXPECT_EQ(::memcmp(buffer, SERIALIZED_TEST_DATA, TEST_DATA.packedSize()), 0);
}

TEST(networking_packets_EntityDelete, deserialization)
{
    EntityDelete data;

    EXPECT_NO_THROW(data = EntityDelete::deserialize(SERIALIZED_TEST_DATA));

    EXPECT_EQ(data.id,   TEST_DATA.id);
}

TEST(networking_packets_EntityDelete, serializeAndDeserialize)
{
    EntityDelete initialData = { .id = 8734738157 };
    EntityDelete deserializedData;
    std::uint8_t buffer[100];

    EXPECT_NO_THROW(initialData.serialize(buffer));
    EXPECT_NO_THROW(deserializedData = EntityDelete::deserialize(buffer));

    EXPECT_EQ(initialData.id,   deserializedData.id);
}

TEST(networking_packets_EntityDelete, smallBufferSerialize)
{
    std::uint8_t buffer[1];

    EXPECT_THROW(TEST_DATA.serialize(buffer), Protecs::SerializationError);
}

TEST(networking_packets_EntityDelete, smallBufferDeserialize)
{
    std::uint8_t buffer[1] = { 'c' };

    EXPECT_THROW(EntityDelete::deserialize(buffer), Protecs::SerializationError);
}
