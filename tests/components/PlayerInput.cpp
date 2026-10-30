/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Unit tests for
** PlayerInput component
*/

#include <gtest/gtest.h>
#include <protecs/components.hpp>
#include <protecs/errors.hpp>
#include <cstring>


using Protecs::Components::PlayerInput;


static constexpr PlayerInput TEST_DATA = { false, true, true, false, true };
static constexpr std::uint8_t SERIALIZED_TEST_DATA[] = {
    0b01101
};


TEST(components_Input, serialization)
{
    std::uint8_t store[100];
    std::uint8_t *buffer = store;

    EXPECT_NO_THROW(TEST_DATA.serialize(buffer, sizeof(store)));
    EXPECT_EQ(buffer - store, PlayerInput::packedSize());
    EXPECT_EQ(::memcmp(store, SERIALIZED_TEST_DATA, PlayerInput::packedSize()), 0);
}

TEST(components_Input, deserialization)
{
    const std::uint8_t *buffer = SERIALIZED_TEST_DATA;

    PlayerInput data;

    EXPECT_NO_THROW(data = PlayerInput::deserialize(buffer, sizeof(SERIALIZED_TEST_DATA)));
    EXPECT_EQ(buffer - SERIALIZED_TEST_DATA, data.packedSize());

    EXPECT_EQ(data.up,      TEST_DATA.up);
    EXPECT_EQ(data.down,    TEST_DATA.down);
    EXPECT_EQ(data.left,    TEST_DATA.left);
    EXPECT_EQ(data.right,   TEST_DATA.right);
    EXPECT_EQ(data.trigger, TEST_DATA.trigger);
}

TEST(components_Input, serializeAndDeserialize)
{
    PlayerInput initialData = { true, false, true, false, false };
    PlayerInput deserializedData;
    std::uint8_t store[100];

    std::uint8_t *outputBuffer = store;
    const std::uint8_t *inputBuffer = store;

    EXPECT_NO_THROW(initialData.serialize(outputBuffer, sizeof(store)));
    EXPECT_NO_THROW(deserializedData = PlayerInput::deserialize(inputBuffer, sizeof(store)));

    EXPECT_EQ(initialData.up,      deserializedData.up);
    EXPECT_EQ(initialData.down,    deserializedData.down);
    EXPECT_EQ(initialData.left,    deserializedData.left);
    EXPECT_EQ(initialData.right,   deserializedData.right);
    EXPECT_EQ(initialData.trigger, deserializedData.trigger);
}

TEST(components_Input, smallBufferSerialize)
{
    std::uint8_t store;
    std::uint8_t* buffer = &store;

    EXPECT_THROW(TEST_DATA.serialize(buffer, 0), Protecs::SerializationError);
}

TEST(components_Input, smallBufferDeserialize)
{
    std::uint8_t store = 'c';
    const std::uint8_t* buffer = &store;

    EXPECT_THROW(PlayerInput::deserialize(buffer, 0), Protecs::SerializationError);
}
