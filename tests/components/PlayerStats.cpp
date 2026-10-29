/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Unit tests for
** PlayerStats component
*/

#include <gtest/gtest.h>
#include <protecs/components.hpp>
#include <protecs/errors.hpp>
#include <protecs/networking.hpp>
#include <cstring>

using Protecs::Components::PlayerStats;


static constexpr PlayerStats TEST_DATA = { 2, 3, 1500 };
static constexpr std::uint8_t SERIALIZED_TEST_DATA[] = {
    0x02,                    // slot
    0x03,                    // lives
    0xdc, 0x05, 0x00, 0x00,  // score
};

TEST(components_PlayerStats, serialization)
{
    std::uint8_t store[100];
    std::uint8_t *buffer = store;

    EXPECT_NO_THROW(TEST_DATA.serialize(buffer, sizeof(store)));
    EXPECT_EQ(buffer - store, PlayerStats::packedSize());
    EXPECT_EQ(::memcmp(store, SERIALIZED_TEST_DATA, PlayerStats::packedSize()), 0);
}

TEST(components_PlayerStats, deserialization)
{
    const std::uint8_t *buffer = SERIALIZED_TEST_DATA;
    PlayerStats data;

    EXPECT_NO_THROW(data = PlayerStats::deserialize(buffer, sizeof(SERIALIZED_TEST_DATA)));
    EXPECT_EQ(buffer - SERIALIZED_TEST_DATA, data.packedSize());
    EXPECT_EQ(data.slot, TEST_DATA.slot);
    EXPECT_EQ(data.lives, TEST_DATA.lives);
    EXPECT_EQ(data.score, TEST_DATA.score);
}

TEST(components_PlayerStats, serializeAndDeserialize)
{
    PlayerStats initialData = { 3, 0, 4000000000 };
    PlayerStats deserializedData;
    std::uint8_t store[100];
    std::uint8_t *outputBuffer = store;
    const std::uint8_t *inputBuffer = store;

    EXPECT_NO_THROW(initialData.serialize(outputBuffer, sizeof(store)));
    EXPECT_NO_THROW(deserializedData = PlayerStats::deserialize(inputBuffer, sizeof(store)));
    EXPECT_EQ(initialData.slot, deserializedData.slot);
    EXPECT_EQ(initialData.lives, deserializedData.lives);
    EXPECT_EQ(initialData.score, deserializedData.score);
}

TEST(components_PlayerStats, smallBufferSerialize)
{
    std::uint8_t store[PlayerStats::packedSize() - 1];
    std::uint8_t* buffer = store;

    EXPECT_THROW(TEST_DATA.serialize(buffer, sizeof(store)), Protecs::SerializationError);
}

TEST(components_PlayerStats, smallBufferDeserialize)
{
    const std::uint8_t* buffer = SERIALIZED_TEST_DATA;

    EXPECT_THROW(PlayerStats::deserialize(buffer, sizeof(SERIALIZED_TEST_DATA) - 1), Protecs::SerializationError);
}

TEST(components_PlayerStats, entityComponentData)
{
    namespace Packets = Protecs::Networking::Packets;

    Packets::EntityComponentData packet = { .entity = 42, .component = TEST_DATA };
    std::vector<std::uint8_t> store(packet.packedSize());
    Packets::EntityComponentData result;

    EXPECT_NO_THROW(packet.serialize(store));
    EXPECT_NO_THROW(result = Packets::EntityComponentData::deserialize(store));
    ASSERT_TRUE(std::holds_alternative<PlayerStats>(result.component));

    const auto& stats = std::get<PlayerStats>(result.component);
    EXPECT_EQ(result.entity, packet.entity);
    EXPECT_EQ(stats.slot, TEST_DATA.slot);
    EXPECT_EQ(stats.lives, TEST_DATA.lives);
    EXPECT_EQ(stats.score, TEST_DATA.score);
}
