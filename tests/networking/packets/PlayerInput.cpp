/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Unit tests for
** PlayerInput packet
*/

#include <gtest/gtest.h>
#include <protecs.hpp>


using Protecs::Networking::Packets::PlayerInput;


static constexpr PlayerInput TEST_DATA = {
    .input = PlayerInput::LEFT,
    .state = PlayerInput::RELEASE,
    .sequence = 10,
};

static constexpr std::uint8_t SERIALIZED_TEST_DATA[] = {
    0x02,  // input
    0x01,  // state
    0x0a,  // sequence
};


TEST(networking_packets_PlayerInput, packedSize)
{
    EXPECT_TRUE(TEST_DATA.packedSize() <= sizeof(TEST_DATA));
    EXPECT_TRUE(TEST_DATA.packedSize() == sizeof(TEST_DATA.input) + sizeof(TEST_DATA.state) + sizeof(TEST_DATA.sequence));
}

TEST(networking_packets_PlayerInput, serialization)
{
    std::uint8_t buffer[100];

    EXPECT_NO_THROW(TEST_DATA.serialize(buffer));
    EXPECT_EQ(::memcmp(buffer, SERIALIZED_TEST_DATA, TEST_DATA.packedSize()), 0);
}

TEST(networking_packets_PlayerInput, deserialization)
{
    PlayerInput data;

    EXPECT_NO_THROW(data = PlayerInput::deserialize(SERIALIZED_TEST_DATA));

    EXPECT_EQ(data.input,    TEST_DATA.input);
    EXPECT_EQ(data.state,    TEST_DATA.state);
    EXPECT_EQ(data.sequence, TEST_DATA.sequence);
}

TEST(networking_packets_PlayerInput, serializeAndDeserialize)
{
    PlayerInput initialData = { .input = PlayerInput::TRIGGER, .state = PlayerInput::HOLD_DOWN, .sequence = 50 };
    PlayerInput deserializedData;
    std::uint8_t buffer[100];

    EXPECT_NO_THROW(initialData.serialize(buffer));
    EXPECT_NO_THROW(deserializedData = PlayerInput::deserialize(buffer));

    EXPECT_EQ(initialData.input,    deserializedData.input);
    EXPECT_EQ(initialData.state,    deserializedData.state);
    EXPECT_EQ(initialData.sequence, deserializedData.sequence);
}

TEST(networking_packets_PlayerInput, smallBufferSerialize)
{
    std::uint8_t buffer[1];

    EXPECT_THROW(TEST_DATA.serialize(buffer), Protecs::SerializationError);
}

TEST(networking_packets_PlayerInput, smallBufferDeserialize)
{
    std::uint8_t buffer[1] = { 'c' };

    EXPECT_THROW(PlayerInput::deserialize(buffer), Protecs::SerializationError);
}
