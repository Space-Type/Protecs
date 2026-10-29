/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Unit tests for
** Movement component
*/

#include <gtest/gtest.h>
#include <protecs/components.hpp>
#include <protecs/errors.hpp>
#include <cstring>


using Protecs::Components::Movement;


static constexpr Movement TEST_DATA = { { 1.5f, -5.2f }, 0.f };
static constexpr std::uint8_t SERIALIZED_TEST_DATA[] = {
    0x00, 0x00, 0xc0, 0x3f,  // position.x
    0x66, 0x66, 0xa6, 0xc0,  // position.y
    0x00, 0x00, 0x00, 0x00,  // angular
};


TEST(components_Movement, serialization)
{
    std::uint8_t store[100];
    std::uint8_t *buffer = store;

    EXPECT_NO_THROW(TEST_DATA.serialize(buffer, sizeof(store)));
    EXPECT_EQ(buffer - store, Movement::packedSize());
    EXPECT_EQ(::memcmp(store, SERIALIZED_TEST_DATA, Movement::packedSize()), 0);
}

TEST(components_Movement, deserialization)
{
    const std::uint8_t *buffer = SERIALIZED_TEST_DATA;

    Movement data;

    EXPECT_NO_THROW(data = Movement::deserialize(buffer, sizeof(SERIALIZED_TEST_DATA)));
    EXPECT_EQ(buffer - SERIALIZED_TEST_DATA, data.packedSize());

    EXPECT_EQ(data.direction.x, TEST_DATA.direction.x);
    EXPECT_EQ(data.direction.y, TEST_DATA.direction.y);
    EXPECT_EQ(data.speed,       TEST_DATA.speed);
}

TEST(components_Movement, serializeAndDeserialize)
{
    Movement initialData = { {-512.981f, 0.f }, -12.3f };
    Movement deserializedData;
    std::uint8_t store[100];

    std::uint8_t *outputBuffer = store;
    const std::uint8_t *inputBuffer = store;

    EXPECT_NO_THROW(initialData.serialize(outputBuffer, sizeof(store)));
    EXPECT_NO_THROW(deserializedData = Movement::deserialize(inputBuffer, sizeof(store)));

    EXPECT_EQ(initialData.direction.x, deserializedData.direction.x);
    EXPECT_EQ(initialData.direction.y, deserializedData.direction.y);
    EXPECT_EQ(initialData.speed,   deserializedData.speed);
}

TEST(components_Movement, smallBufferSerialize)
{
    std::uint8_t store;
    std::uint8_t* buffer = &store;

    EXPECT_THROW(TEST_DATA.serialize(buffer, sizeof(store)), Protecs::SerializationError);
}

TEST(components_Movement, smallBufferDeserialize)
{
    std::uint8_t store = 'c';
    const std::uint8_t* buffer = &store;

    EXPECT_THROW(Movement::deserialize(buffer, sizeof(store)), Protecs::SerializationError);
}
