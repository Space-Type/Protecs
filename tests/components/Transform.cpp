/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Unit tests for
** Transform component
*/

#include <gtest/gtest.h>
#include <protecs/components.hpp>
#include <protecs/errors.hpp>
#include <cstring>


using Protecs::Components::Transform;


static constexpr Transform TEST_DATA = { { 1.5f, -5.2f }, 0.f, 50.f };
static constexpr std::uint8_t SERIALIZED_TEST_DATA[] = {
    0x00, 0x00, 0xc0, 0x3f,  // position.x
    0x66, 0x66, 0xa6, 0xc0,  // position.y
    0x00, 0x00, 0x00, 0x00,  // rotation
    0x00, 0x00, 0x48, 0x42,  // scale
};


TEST(components_Transform, serialization)
{
    std::uint8_t store[100];
    std::uint8_t *buffer = store;

    EXPECT_NO_THROW(TEST_DATA.serialize(buffer, sizeof(store)));
    EXPECT_EQ(buffer - store, Transform::packedSize());
    EXPECT_EQ(::memcmp(store, SERIALIZED_TEST_DATA, Transform::packedSize()), 0);
}

TEST(components_Transform, deserialization)
{
    const std::uint8_t *buffer = SERIALIZED_TEST_DATA;

    Transform data;

    EXPECT_NO_THROW(data = Transform::deserialize(buffer, sizeof(SERIALIZED_TEST_DATA)));
    EXPECT_EQ(buffer - SERIALIZED_TEST_DATA, data.packedSize());

    EXPECT_EQ(data.position.x, TEST_DATA.position.x);
    EXPECT_EQ(data.position.y, TEST_DATA.position.y);
    EXPECT_EQ(data.rotation,   TEST_DATA.rotation);
    EXPECT_EQ(data.scale,      TEST_DATA.scale);
}

TEST(components_Transform, serializeAndDeserialize)
{
    Transform initialData = { {-512.981f, 0.f }, -12.3f, 123.123f };
    Transform deserializedData;
    std::uint8_t store[100];

    std::uint8_t *outputBuffer = store;
    const std::uint8_t *inputBuffer = store;

    EXPECT_NO_THROW(initialData.serialize(outputBuffer, sizeof(store)));
    EXPECT_NO_THROW(deserializedData = Transform::deserialize(inputBuffer, sizeof(store)));

    EXPECT_EQ(initialData.position.x, deserializedData.position.x);
    EXPECT_EQ(initialData.position.y, deserializedData.position.y);
    EXPECT_EQ(initialData.rotation,   deserializedData.rotation);
    EXPECT_EQ(initialData.scale,      deserializedData.scale);
}

TEST(components_Transform, smallBufferSerialize)
{
    Transform data = { { 1.5f, -5.2f }, 0.f, 50.f };

    std::uint8_t store;
    std::uint8_t* buffer = &store;

    EXPECT_THROW(data.serialize(buffer, sizeof(store)), Protecs::SerializationError);
}

TEST(components_Transform, smallBufferDeserialize)
{
    std::uint8_t store = 'c';
    const std::uint8_t* buffer = &store;

    EXPECT_THROW(Transform::deserialize(buffer, sizeof(store)), Protecs::SerializationError);
}
