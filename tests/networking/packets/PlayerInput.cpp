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
    .simulationTick = 255,
    .sequence = 10,
    .input = PlayerInput::LEFT,
    .state = PlayerInput::RELEASE,
};

static constexpr std::uint8_t SERIALIZED_TEST_DATA[] = {
    0xff, 0x00, 0x00, 0x00,  // simulationTick
    0x0a,                    // sequence
    0x02,                    // input
    0x01,                    // state
};


TEST(networking_packets_PlayerInput, packedSize)
{
    EXPECT_TRUE(TEST_DATA.packedSize() <= sizeof(TEST_DATA));
    EXPECT_TRUE(TEST_DATA.packedSize() == sizeof(TEST_DATA.simulationTick) + sizeof(TEST_DATA.input) + sizeof(TEST_DATA.state) + sizeof(TEST_DATA.sequence));
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

    EXPECT_EQ(data.simulationTick, TEST_DATA.simulationTick);
    EXPECT_EQ(data.sequence,       TEST_DATA.sequence);
    EXPECT_EQ(data.input,          TEST_DATA.input);
    EXPECT_EQ(data.state,          TEST_DATA.state);
}

TEST(networking_packets_PlayerInput, serializeAndDeserialize)
{
    PlayerInput initialData = { .simulationTick = 78512, .sequence = 50, .input = PlayerInput::TRIGGER, .state = PlayerInput::HOLD_DOWN };
    PlayerInput deserializedData;
    std::uint8_t buffer[100];

    EXPECT_NO_THROW(initialData.serialize(buffer));
    EXPECT_NO_THROW(deserializedData = PlayerInput::deserialize(buffer));

    EXPECT_EQ(initialData.simulationTick, deserializedData.simulationTick);
    EXPECT_EQ(initialData.sequence,       deserializedData.sequence);
    EXPECT_EQ(initialData.input,          deserializedData.input);
    EXPECT_EQ(initialData.state,          deserializedData.state);
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

TEST(networking_packets_PlayerInput, packetName)
{
    EXPECT_EQ(PlayerInput::packetName(), "player-input");
}
