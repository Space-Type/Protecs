/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Unit tests for
** EntitySyncComponents packet
*/

#include <gtest/gtest.h>
#include <protecs.hpp>


using Protecs::Networking::Packets::EntitySyncComponents;


static constexpr EntitySyncComponents TEST_DATA = {
    .entity = 751937,
    .signature = 12,
};

static constexpr std::uint8_t SERIALIZED_TEST_DATA[] = {
    0x41, 0x79, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00,  // entity
    0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // signature
};


TEST(networking_packets_EntitySyncComponents, packedSize)
{
    EXPECT_LE(TEST_DATA.packedSize(), sizeof(TEST_DATA));

    // Note:
    // The following test only holds true if
    // Wrecks::Signature is a multiple of 64
    // (implementation defined)
    EXPECT_EQ(TEST_DATA.packedSize(), sizeof(TEST_DATA.entity) + sizeof(TEST_DATA.signature));
}

TEST(networking_packets_EntitySyncComponents, serialization)
{
    std::uint8_t buffer[100];

    EXPECT_NO_THROW(TEST_DATA.serialize(buffer));
    EXPECT_EQ(::memcmp(buffer, SERIALIZED_TEST_DATA, TEST_DATA.packedSize()), 0);
}

TEST(networking_packets_EntitySyncComponents, deserialization)
{
    EntitySyncComponents data;

    EXPECT_NO_THROW(data = EntitySyncComponents::deserialize(SERIALIZED_TEST_DATA));

    EXPECT_EQ(data.entity,    TEST_DATA.entity);
    EXPECT_EQ(data.signature, TEST_DATA.signature);
}

TEST(networking_packets_EntitySyncComponents, serializeAndDeserialize)
{
    EntitySyncComponents initialData = { .entity = 8734738157, .signature = 0b0110001001100000111 };
    EntitySyncComponents deserializedData;
    std::uint8_t buffer[100];

    EXPECT_NO_THROW(initialData.serialize(buffer));
    EXPECT_NO_THROW(deserializedData = EntitySyncComponents::deserialize(buffer));

    EXPECT_EQ(initialData.entity,    deserializedData.entity);
    EXPECT_EQ(initialData.signature, deserializedData.signature);
}

TEST(networking_packets_EntitySyncComponents, smallBufferSerialize)
{
    std::uint8_t buffer[1];

    EXPECT_THROW(TEST_DATA.serialize(buffer), Protecs::SerializationError);
}

TEST(networking_packets_EntitySyncComponents, smallBufferDeserialize)
{
    std::uint8_t buffer[1] = { 'c' };

    EXPECT_THROW(EntitySyncComponents::deserialize(buffer), Protecs::SerializationError);
}
