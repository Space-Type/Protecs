/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Unit tests for
** PathFinding component
*/

#include <gtest/gtest.h>
#include <protecs/components.hpp>
#include <protecs/errors.hpp>
#include <cstring>


using Protecs::Components::PathFinding;


static constexpr PathFinding TEST_DATA = { .type = PathFinding::STRAIGHT, .targetVelocity = { 1.2f, -0.9f }, .acceleration = 0.5f };
static constexpr std::uint8_t SERIALIZED_TEST_DATA[] = {
                      0x00,  // type
    0x9a, 0x99, 0x99, 0x3f,  // targetVelocity.x
    0x66, 0x66, 0x66, 0xbf,  // targetVelocity.y
    0x00, 0x00, 0x00, 0x3f,  // acceleration
};


TEST(components_PathFinding, serialization)
{
    std::uint8_t store[100];
    std::uint8_t *buffer = store;

    EXPECT_NO_THROW(TEST_DATA.serialize(buffer, sizeof(store)));
    EXPECT_EQ(buffer - store, PathFinding::packedSize());
    EXPECT_EQ(::memcmp(store, SERIALIZED_TEST_DATA, PathFinding::packedSize()), 0);
}

TEST(components_PathFinding, deserialization)
{
    const std::uint8_t *buffer = SERIALIZED_TEST_DATA;

    PathFinding data;

    EXPECT_NO_THROW(data = PathFinding::deserialize(buffer, sizeof(SERIALIZED_TEST_DATA)));
    EXPECT_EQ(buffer - SERIALIZED_TEST_DATA, data.packedSize());

    EXPECT_EQ(data.type,             TEST_DATA.type);
    EXPECT_EQ(data.targetVelocity.x, TEST_DATA.targetVelocity.x);
    EXPECT_EQ(data.targetVelocity.y, TEST_DATA.targetVelocity.y);
    EXPECT_EQ(data.acceleration,     TEST_DATA.acceleration);
}

TEST(components_PathFinding, serializeAndDeserialize)
{
    PathFinding initialData = { PathFinding::STRAIGHT, {-512.981f, 0.f }, -12.3f };
    PathFinding deserializedData;
    std::uint8_t store[100];

    std::uint8_t *outputBuffer = store;
    const std::uint8_t *inputBuffer = store;

    EXPECT_NO_THROW(initialData.serialize(outputBuffer, sizeof(store)));
    EXPECT_NO_THROW(deserializedData = PathFinding::deserialize(inputBuffer, sizeof(store)));

    EXPECT_EQ(initialData.type,             deserializedData.type);
    EXPECT_EQ(initialData.targetVelocity.x, deserializedData.targetVelocity.x);
    EXPECT_EQ(initialData.targetVelocity.y, deserializedData.targetVelocity.y);
    EXPECT_EQ(initialData.acceleration,     deserializedData.acceleration);
}

TEST(components_PathFinding, smallBufferSerialize)
{
    std::uint8_t store;
    std::uint8_t* buffer = &store;

    EXPECT_THROW(TEST_DATA.serialize(buffer, sizeof(store)), Protecs::SerializationError);
}

TEST(components_PathFinding, smallBufferDeserialize)
{
    std::uint8_t store = 'c';
    const std::uint8_t* buffer = &store;

    EXPECT_THROW(PathFinding::deserialize(buffer, sizeof(store)), Protecs::SerializationError);
}
