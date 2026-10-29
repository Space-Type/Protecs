/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Unit tests for
** EntityList packet
*/

#include <gtest/gtest.h>
#include <protecs.hpp>


using Protecs::Networking::Packets::EntityList;


static const EntityList TEST_DATA = {
    .entities = {{ { 751937, 12 }, }}
};

static constexpr std::uint8_t SERIALIZED_TEST_DATA[] = {
    0x01, 0x00, 0x00, 0x00,                          // size
    0x41, 0x79, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00,  // entities[0].first
    0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // entities[0].second
};


TEST(networking_packets_EntityList, packedSize)
{
    EXPECT_EQ(TEST_DATA.entities.size(), 1);
    EXPECT_EQ(TEST_DATA.packedSize(), TEST_DATA.partialPackedSize() + sizeof(TEST_DATA.entities[0].first) + sizeof(TEST_DATA.entities[0].second));
}

TEST(networking_packets_EntityList, serialization)
{
    std::uint8_t buffer[100];

    EXPECT_NO_THROW(TEST_DATA.serialize(buffer));
    EXPECT_EQ(::memcmp(buffer, SERIALIZED_TEST_DATA, TEST_DATA.packedSize()), 0);
}

TEST(networking_packets_EntityList, deserialization)
{
    EntityList data;

    EXPECT_NO_THROW(data = EntityList::deserialize(SERIALIZED_TEST_DATA));

    EXPECT_EQ(data.entities.size(),    TEST_DATA.entities.size());
    EXPECT_EQ(data.entities[0].first,  TEST_DATA.entities[0].first);
    EXPECT_EQ(data.entities[0].second, TEST_DATA.entities[0].second);
}

TEST(networking_packets_EntityList, serializeAndDeserialize)
{
    EntityList initialData = {{ { 123, 321 }, { 456, 654 } }};
    EntityList deserializedData;
    std::uint8_t buffer[100];

    EXPECT_NO_THROW(initialData.serialize(buffer));
    EXPECT_NO_THROW(deserializedData = EntityList::deserialize(buffer));

    EXPECT_EQ(initialData.entities.size(),    deserializedData.entities.size());
    EXPECT_EQ(initialData.entities[0].first,  deserializedData.entities[0].first);
    EXPECT_EQ(initialData.entities[0].second, deserializedData.entities[0].second);
    EXPECT_EQ(initialData.entities[1].first,  deserializedData.entities[1].first);
    EXPECT_EQ(initialData.entities[1].second, deserializedData.entities[1].second);
}

TEST(networking_packets_EntityList, serializeAndDeserializeEmpty)
{
    EntityList initialData;
    EntityList deserializedData;
    std::uint8_t buffer[100];

    EXPECT_NO_THROW(initialData.serialize(buffer));
    EXPECT_NO_THROW(deserializedData = EntityList::deserialize(buffer));

    EXPECT_EQ(initialData.entities.size(), deserializedData.entities.size());
}

TEST(networking_packets_EntityList, smallBufferSerialize)
{
    std::uint8_t buffer[1];

    EXPECT_THROW(TEST_DATA.serialize(buffer), Protecs::SerializationError);
}

TEST(networking_packets_EntityList, smallBufferDeserialize)
{
    std::uint8_t buffer1[1] = { 'c' };
    std::uint8_t buffer2[5] = { 0x12 };

    EXPECT_THROW(EntityList::deserialize(buffer1), Protecs::SerializationError);
    EXPECT_THROW(EntityList::deserialize(buffer2), Protecs::SerializationError);
}
