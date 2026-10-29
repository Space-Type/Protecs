/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Unit tests for
** EntityComponentData packet
*/

#include <gtest/gtest.h>
#include <protecs.hpp>


using Protecs::Networking::Packets::EntityComponentData;


static constexpr EntityComponentData TEST_DATA = {
    .entity    = 751937,
    .component = Protecs::Components::Level{ 52, 3 },
};

static constexpr std::uint8_t SERIALIZED_TEST_DATA[] = {
    0x41, 0x79, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00,  // entity
    0x00, 0x00,                                      // component type
    0x34, 0x00, 0x00, 0x00, 0x03,                    // component data
};


TEST(networking_packets_EntityComponentData, packedSize)
{
    EXPECT_LE(TEST_DATA.packedSize(), sizeof(TEST_DATA));
}

TEST(networking_packets_EntityComponentData, serialization)
{
    std::uint8_t buffer[100];

    EXPECT_NO_THROW(TEST_DATA.serialize(buffer));
    EXPECT_EQ(::memcmp(buffer, SERIALIZED_TEST_DATA, TEST_DATA.packedSize()), 0);
}

TEST(networking_packets_EntityComponentData, deserialization)
{
    EntityComponentData data;

    EXPECT_NO_THROW(data = EntityComponentData::deserialize(SERIALIZED_TEST_DATA));

    EXPECT_EQ(data.entity, TEST_DATA.entity);
    EXPECT_EQ(data.component.index(), TEST_DATA.component.index());
}

TEST(networking_packets_EntityComponentData, smallBufferSerialize)
{
    std::uint8_t buffer[1];

    EXPECT_THROW(TEST_DATA.serialize(buffer), Protecs::SerializationError);
}

TEST(networking_packets_EntityComponentData, smallBufferDeserialize)
{
    std::uint8_t buffer[1] = { 'c' };

    EXPECT_THROW(EntityComponentData::deserialize(buffer), Protecs::SerializationError);
}

TEST(networking_packets_EntityComponentData, deserializeInvalidComponent)
{
    std::uint8_t buffer[10] = {
        0x52, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0xff, 0x53,
    };

    EXPECT_THROW(EntityComponentData::deserialize(buffer), Protecs::SerializationError);
}

TEST(networking_packets_EntityComponentData, serializeAndDeserializeLevel)
{
    using Protecs::Components::Transform;

    EntityComponentData initialData = { .entity = 8734738157, .component = Transform{ { 1.2f, -5.3f }, 0.3f } };
    EntityComponentData deserializedData;
    std::uint8_t buffer[100];

    EXPECT_NO_THROW(initialData.serialize(buffer));
    EXPECT_NO_THROW(deserializedData = EntityComponentData::deserialize(buffer));

    EXPECT_EQ(initialData.entity,            deserializedData.entity);
    EXPECT_EQ(initialData.component.index(), deserializedData.component.index());
}

TEST(networking_packets_EntityComponentData, serializeAndDeserializePathFinding)
{
    using Protecs::Components::PathFinding;

    EntityComponentData initialData = { .entity = 1234, .component = PathFinding{ PathFinding::STRAIGHT, { 1.2f, -5.3f }, 0.3f } };
    EntityComponentData deserializedData;
    std::uint8_t buffer[100];

    EXPECT_NO_THROW(initialData.serialize(buffer));
    EXPECT_NO_THROW(deserializedData = EntityComponentData::deserialize(buffer));

    EXPECT_EQ(initialData.entity,            deserializedData.entity);
    EXPECT_EQ(initialData.component.index(), deserializedData.component.index());
}

TEST(networking_packets_EntityComponentData, serializeAndDeserializePlayerStats)
{
    using Protecs::Components::PlayerStats;

    EntityComponentData initialData = { .entity = 1234, .component = PlayerStats{ 2, 3, 5123 } };
    EntityComponentData deserializedData;
    std::uint8_t buffer[100];

    EXPECT_NO_THROW(initialData.serialize(buffer));
    EXPECT_NO_THROW(deserializedData = EntityComponentData::deserialize(buffer));

    EXPECT_EQ(initialData.entity,            deserializedData.entity);
    EXPECT_EQ(initialData.component.index(), deserializedData.component.index());
}

TEST(networking_packets_EntityComponentData, serializeAndDeserializeTransform)
{
    using Protecs::Components::Transform;

    EntityComponentData initialData = { .entity = 1234, .component = Transform{ { 1.2f, -5.3f }, 0.3f } };
    EntityComponentData deserializedData;
    std::uint8_t buffer[100];

    EXPECT_NO_THROW(initialData.serialize(buffer));
    EXPECT_NO_THROW(deserializedData = EntityComponentData::deserialize(buffer));

    EXPECT_EQ(initialData.entity,            deserializedData.entity);
    EXPECT_EQ(initialData.component.index(), deserializedData.component.index());
}

TEST(networking_packets_EntityComponentData, serializeAndDeserializeVelocity)
{
    using Protecs::Components::Velocity;

    EntityComponentData initialData = { .entity = 1234, .component = Velocity{ { 1.2f, -5.3f }, 0.3f } };
    EntityComponentData deserializedData;
    std::uint8_t buffer[100];

    EXPECT_NO_THROW(initialData.serialize(buffer));
    EXPECT_NO_THROW(deserializedData = EntityComponentData::deserialize(buffer));

    EXPECT_EQ(initialData.entity,            deserializedData.entity);
    EXPECT_EQ(initialData.component.index(), deserializedData.component.index());
}
