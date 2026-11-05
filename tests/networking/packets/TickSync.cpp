/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Unit tests for
** TickSync packet
*/

#include <gtest/gtest.h>
#include <protecs.hpp>


using Protecs::Networking::Packets::TickSync;


static constexpr TickSync TEST_DATA = {
    .clientTick = 5,
    .serverTick = 10,
    .serverTime = std::chrono::steady_clock::time_point(std::chrono::nanoseconds(255)),
};

static constexpr std::uint8_t SERIALIZED_TEST_DATA[] = {
    0x05, 0x00, 0x00, 0x00,                          // clientTick
    0x0a, 0x00, 0x00, 0x00,                          // serverTick
    0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // serverTime
};


TEST(networking_packets_TickSync, packedSize)
{
    EXPECT_TRUE(TEST_DATA.packedSize() == sizeof(TEST_DATA));
}

TEST(networking_packets_TickSync, serialization)
{
    std::uint8_t buffer[100];

    EXPECT_NO_THROW(TEST_DATA.serialize(buffer));
    EXPECT_EQ(::memcmp(buffer, SERIALIZED_TEST_DATA, TEST_DATA.packedSize()), 0);
}

TEST(networking_packets_TickSync, deserialization)
{
    TickSync data;

    EXPECT_NO_THROW(data = TickSync::deserialize(SERIALIZED_TEST_DATA));

    EXPECT_EQ(data.clientTick, TEST_DATA.clientTick);
    EXPECT_EQ(data.serverTick, TEST_DATA.serverTick);
    EXPECT_EQ(data.serverTime, TEST_DATA.serverTime);
}

TEST(networking_packets_TickSync, serializeAndDeserialize)
{
    TickSync initialData = { 652, 89352, std::chrono::steady_clock::now() };
    TickSync deserializedData;
    std::uint8_t buffer[100];

    EXPECT_NO_THROW(initialData.serialize(buffer));
    EXPECT_NO_THROW(deserializedData = TickSync::deserialize(buffer));

    EXPECT_EQ(initialData.clientTick, deserializedData.clientTick);
    EXPECT_EQ(initialData.serverTick, deserializedData.serverTick);
    EXPECT_EQ(initialData.serverTime, deserializedData.serverTime);
}

TEST(networking_packets_TickSync, smallBufferSerialize)
{
    std::uint8_t buffer[1];

    EXPECT_THROW(TEST_DATA.serialize(buffer), Protecs::SerializationError);
}

TEST(networking_packets_TickSync, smallBufferDeserialize)
{
    std::uint8_t buffer[1] = { 'c' };

    EXPECT_THROW(TickSync::deserialize(buffer), Protecs::SerializationError);
}

TEST(networking_packets_TickSync, packetName)
{
    EXPECT_EQ(TickSync::packetName(), "tick-sync");
}
