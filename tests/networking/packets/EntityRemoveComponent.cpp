/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Unit tests for
** EntityRemoveComponent packet
*/

#include <gtest/gtest.h>
#include <protecs.hpp>


using Protecs::Networking::Packets::EntityRemoveComponent;


static constexpr EntityRemoveComponent TEST_DATA = {
    .entity = 751937,
    .type = 12,
};

static constexpr std::uint8_t SERIALIZED_TEST_DATA[] = {
    0x41, 0x79, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00,  // entity
    0x0c, 0x00,                                      // type

};


TEST(networking_packets_EntityRemoveComponent, packedSize)
{
    EXPECT_LE(TEST_DATA.packedSize(), sizeof(TEST_DATA));
    EXPECT_EQ(TEST_DATA.packedSize(), sizeof(TEST_DATA.entity) + sizeof(TEST_DATA.type));
}

TEST(networking_packets_EntityRemoveComponent, serialization)
{
    std::uint8_t buffer[100];

    EXPECT_NO_THROW(TEST_DATA.serialize(buffer));
    EXPECT_EQ(::memcmp(buffer, SERIALIZED_TEST_DATA, TEST_DATA.packedSize()), 0);
}

TEST(networking_packets_EntityRemoveComponent, deserialization)
{
    EntityRemoveComponent data;

    EXPECT_NO_THROW(data = EntityRemoveComponent::deserialize(SERIALIZED_TEST_DATA));

    EXPECT_EQ(data.entity, TEST_DATA.entity);
    EXPECT_EQ(data.type,   TEST_DATA.type);
}

TEST(networking_packets_EntityRemoveComponent, serializeAndDeserialize)
{
    EntityRemoveComponent initialData = { .entity = 8734738157, .type = 52 };
    EntityRemoveComponent deserializedData;
    std::uint8_t buffer[100];

    EXPECT_NO_THROW(initialData.serialize(buffer));
    EXPECT_NO_THROW(deserializedData = EntityRemoveComponent::deserialize(buffer));

    EXPECT_EQ(initialData.entity, deserializedData.entity);
    EXPECT_EQ(initialData.type,   deserializedData.type);
}

TEST(networking_packets_EntityRemoveComponent, smallBufferSerialize)
{
    std::uint8_t buffer[1];

    EXPECT_THROW(TEST_DATA.serialize(buffer), Protecs::SerializationError);
}

TEST(networking_packets_EntityRemoveComponent, smallBufferDeserialize)
{
    std::uint8_t buffer[1] = { 'c' };

    EXPECT_THROW(EntityRemoveComponent::deserialize(buffer), Protecs::SerializationError);
}
