/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Unit tests for
** EntityCreate packet
*/

#include <gtest/gtest.h>
#include <protecs.hpp>


using Protecs::Networking::Packets::EntityCreate;


static constexpr EntityCreate TEST_DATA = {
    .id   = 751937,
    .type = EntityCreate::ENEMY_PATA_PATA,
};

static constexpr std::uint8_t SERIALIZED_TEST_DATA[] = {
    0x41, 0x79, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00,  // id
    EntityCreate::ENEMY_PATA_PATA,                   // type
};


TEST(networking_packets_EntityCreate, packedSize)
{
    EXPECT_LE(TEST_DATA.packedSize(), sizeof(TEST_DATA));
    EXPECT_EQ(TEST_DATA.packedSize(), sizeof(TEST_DATA.id) + sizeof(TEST_DATA.type));
}

TEST(networking_packets_EntityCreate, serialization)
{
    std::uint8_t buffer[100];

    EXPECT_NO_THROW(TEST_DATA.serialize(buffer));
    EXPECT_EQ(::memcmp(buffer, SERIALIZED_TEST_DATA, TEST_DATA.packedSize()), 0);
}

TEST(networking_packets_EntityCreate, deserialization)
{
    EntityCreate data;

    EXPECT_NO_THROW(data = EntityCreate::deserialize(SERIALIZED_TEST_DATA));

    EXPECT_EQ(data.id,   TEST_DATA.id);
    EXPECT_EQ(data.type, TEST_DATA.type);
}

TEST(networking_packets_EntityCreate, serializeAndDeserialize)
{
    EntityCreate initialData = { .id = 8734738157, .type = EntityCreate::PLAYER };
    EntityCreate deserializedData;
    std::uint8_t buffer[100];

    EXPECT_NO_THROW(initialData.serialize(buffer));
    EXPECT_NO_THROW(deserializedData = EntityCreate::deserialize(buffer));

    EXPECT_EQ(initialData.id,   deserializedData.id);
    EXPECT_EQ(initialData.type, deserializedData.type);
}

TEST(networking_packets_EntityCreate, smallBufferSerialize)
{
    std::uint8_t buffer[1];

    EXPECT_THROW(TEST_DATA.serialize(buffer), Protecs::SerializationError);
}

TEST(networking_packets_EntityCreate, smallBufferDeserialize)
{
    std::uint8_t buffer[1] = { 'c' };

    EXPECT_THROW(EntityCreate::deserialize(buffer), Protecs::SerializationError);
}
