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


using Protecs::Components::Level;


static constexpr Level TEST_DATA = { 52, 8 };
static constexpr std::uint8_t SERIALIZED_TEST_DATA[] = {
    0x34, 0x00, 0x00, 0x00,  // progression
    0x08,                    // stage
};


TEST(components_Level, serialization)
{
    std::uint8_t store[100];
    std::uint8_t *buffer = store;

    EXPECT_NO_THROW(TEST_DATA.serialize(buffer, sizeof(store)));
    EXPECT_EQ(buffer - store, Level::packedSize());
    EXPECT_EQ(::memcmp(store, SERIALIZED_TEST_DATA, Level::packedSize()), 0);
}

TEST(components_Level, deserialization)
{
    const std::uint8_t *buffer = SERIALIZED_TEST_DATA;

    Level data;

    EXPECT_NO_THROW(data = Level::deserialize(buffer, sizeof(SERIALIZED_TEST_DATA)));
    EXPECT_EQ(buffer - SERIALIZED_TEST_DATA, data.packedSize());

    EXPECT_EQ(data.progression, TEST_DATA.progression);
    EXPECT_EQ(data.stage, TEST_DATA.stage);
}

TEST(components_Level, serializeAndDeserialize)
{
    Level initialData = { 127318314, 1 };
    Level deserializedData;
    std::uint8_t store[100];

    std::uint8_t *outputBuffer = store;
    const std::uint8_t *inputBuffer = store;

    EXPECT_NO_THROW(initialData.serialize(outputBuffer, sizeof(store)));
    EXPECT_NO_THROW(deserializedData = Level::deserialize(inputBuffer, sizeof(store)));

    EXPECT_EQ(initialData.progression, deserializedData.progression);
    EXPECT_EQ(initialData.stage, deserializedData.stage);
}

TEST(components_Level, smallBufferSerialize)
{
    std::uint8_t store;
    std::uint8_t* buffer = &store;

    EXPECT_THROW(TEST_DATA.serialize(buffer, sizeof(store)), Protecs::SerializationError);
}

TEST(components_Level, smallBufferDeserialize)
{
    std::uint8_t store = 'c';
    const std::uint8_t* buffer = &store;

    EXPECT_THROW(Level::deserialize(buffer, sizeof(store)), Protecs::SerializationError);
}
