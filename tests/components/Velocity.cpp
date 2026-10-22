/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Unit tests for
** Velocity component
*/

#include <gtest/gtest.h>
#include <protecs/components.hpp>
#include <protecs/errors.hpp>
#include <cstring>


using Protecs::Components::Velocity;


static constexpr Velocity TEST_DATA = { { 1.5f, -5.2f }, 0.f };
static constexpr std::uint8_t SERIALIZED_TEST_DATA[] = {
    0x00, 0x00, 0xc0, 0x3f,  // position.x
    0x66, 0x66, 0xa6, 0xc0,  // position.y
    0x00, 0x00, 0x00, 0x00,  // angular
};


TEST(components_Velocity, serialization)
{
    std::uint8_t store[100];
    std::uint8_t *buffer = store;

    EXPECT_NO_THROW(TEST_DATA.serialize(buffer, sizeof(store)));
    EXPECT_EQ(buffer - store, Velocity::packedSize());
    EXPECT_EQ(::memcmp(store, SERIALIZED_TEST_DATA, Velocity::packedSize()), 0);
}

TEST(components_Velocity, deserialization)
{
    const std::uint8_t *buffer = SERIALIZED_TEST_DATA;

    Velocity data;

    EXPECT_NO_THROW(data = Velocity::deserialize(buffer, sizeof(SERIALIZED_TEST_DATA)));
    EXPECT_EQ(buffer - SERIALIZED_TEST_DATA, data.packedSize());

    EXPECT_EQ(data.position.x, TEST_DATA.position.x);
    EXPECT_EQ(data.position.y, TEST_DATA.position.y);
    EXPECT_EQ(data.angular,   TEST_DATA.angular);
}

TEST(components_Velocity, serializeAndDeserialize)
{
    Velocity initialData = { {-512.981f, 0.f }, -12.3f };
    Velocity deserializedData;
    std::uint8_t store[100];

    std::uint8_t *outputBuffer = store;
    const std::uint8_t *inputBuffer = store;

    EXPECT_NO_THROW(initialData.serialize(outputBuffer, sizeof(store)));
    EXPECT_NO_THROW(deserializedData = Velocity::deserialize(inputBuffer, sizeof(store)));

    EXPECT_EQ(initialData.position.x, deserializedData.position.x);
    EXPECT_EQ(initialData.position.y, deserializedData.position.y);
    EXPECT_EQ(initialData.angular,   deserializedData.angular);
}

TEST(components_Velocity, smallBufferSerialize)
{
    std::uint8_t store;
    std::uint8_t* buffer = &store;

    EXPECT_THROW(TEST_DATA.serialize(buffer, sizeof(store)), Protecs::SerializationError);
}

TEST(components_Velocity, smallBufferDeserialize)
{
    std::uint8_t store = 'c';
    const std::uint8_t* buffer = &store;

    EXPECT_THROW(Velocity::deserialize(buffer, sizeof(store)), Protecs::SerializationError);
}
