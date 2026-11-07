/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Unit tests for
** PlayerName component
*/

#include <gtest/gtest.h>
#include <protecs/components.hpp>
#include <protecs/errors.hpp>
#include <protecs/networking.hpp>
#include <cstring>
#include <string>

using Protecs::Components::PlayerName;


static const PlayerName TEST_DATA = PlayerName::fromStr("Bard");
static constexpr std::uint8_t SERIALIZED_TEST_DATA[] = {
    0x04,                    // length
    'B', 'a', 'r', 'd',      // name
};

TEST(components_PlayerName, fromStr)
{
    EXPECT_EQ(TEST_DATA.length, 4);
    EXPECT_EQ(TEST_DATA.str(), "Bard");
    EXPECT_EQ(PlayerName::fromStr("").str(), "");
}

TEST(components_PlayerName, fromStrTruncatesLongNames)
{
    std::string name(PlayerName::MAX_LENGTH + 10, 'x');

    EXPECT_EQ(PlayerName::fromStr(name).str(), std::string(PlayerName::MAX_LENGTH, 'x'));
}

TEST(components_PlayerName, serialization)
{
    std::uint8_t store[100];
    std::uint8_t *buffer = store;

    EXPECT_NO_THROW(TEST_DATA.serialize(buffer, sizeof(store)));
    EXPECT_EQ(buffer - store, TEST_DATA.packedSize());
    EXPECT_EQ(::memcmp(store, SERIALIZED_TEST_DATA, sizeof(SERIALIZED_TEST_DATA)), 0);
}

TEST(components_PlayerName, deserialization)
{
    const std::uint8_t *buffer = SERIALIZED_TEST_DATA;
    PlayerName data;

    EXPECT_NO_THROW(data = PlayerName::deserialize(buffer, sizeof(SERIALIZED_TEST_DATA)));
    EXPECT_EQ(buffer - SERIALIZED_TEST_DATA, data.packedSize());
    EXPECT_EQ(data.str(), "Bard");
}

TEST(components_PlayerName, serializeAndDeserializeLongestName)
{
    PlayerName initialData = PlayerName::fromStr(std::string(PlayerName::MAX_LENGTH, 'z'));
    PlayerName deserializedData;
    std::uint8_t store[100];
    std::uint8_t *outputBuffer = store;
    const std::uint8_t *inputBuffer = store;

    EXPECT_NO_THROW(initialData.serialize(outputBuffer, sizeof(store)));
    EXPECT_NO_THROW(deserializedData = PlayerName::deserialize(inputBuffer, sizeof(store)));
    EXPECT_EQ(initialData.str(), deserializedData.str());
}

TEST(components_PlayerName, smallBufferSerialize)
{
    std::uint8_t store[sizeof(SERIALIZED_TEST_DATA) - 1];
    std::uint8_t* buffer = store;

    EXPECT_THROW(TEST_DATA.serialize(buffer, sizeof(store)), Protecs::SerializationError);
}

TEST(components_PlayerName, smallBufferDeserialize)
{
    const std::uint8_t* buffer = SERIALIZED_TEST_DATA;

    EXPECT_THROW(PlayerName::deserialize(buffer, sizeof(SERIALIZED_TEST_DATA) - 1), Protecs::SerializationError);
    buffer = SERIALIZED_TEST_DATA;
    EXPECT_THROW(PlayerName::deserialize(buffer, 0), Protecs::SerializationError);
}

TEST(components_PlayerName, tooLongLengthSerialize)
{
    PlayerName data = PlayerName::fromStr("Bard");
    std::uint8_t store[100];
    std::uint8_t* buffer = store;

    data.length = PlayerName::MAX_LENGTH + 1;
    EXPECT_THROW(data.serialize(buffer, sizeof(store)), Protecs::SerializationError);
}

TEST(components_PlayerName, tooLongLengthIsRejected)
{
    std::uint8_t store[300] = { 0xff };  // length 255, enough bytes behind it
    const std::uint8_t* buffer = store;

    EXPECT_THROW(PlayerName::deserialize(buffer, sizeof(store)), Protecs::SerializationError);
}

TEST(components_PlayerName, existingComponentIndicesAreUnchanged)
{
    using Protecs::Components::Manager;

    EXPECT_EQ(Manager::index<Protecs::Components::Velocity>() + 1, Manager::index<PlayerName>());
}
