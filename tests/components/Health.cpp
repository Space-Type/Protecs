/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Unit tests for
** Health component
*/

#include <gtest/gtest.h>
#include <protecs/components.hpp>
#include <protecs/errors.hpp>
#include <protecs/networking.hpp>
#include <cstring>

using Protecs::Components::Health;


static constexpr Health TEST_DATA = { 3, 20 };
static constexpr std::uint8_t SERIALIZED_TEST_DATA[] = {
    0x03, 0x00,  // hp
    0x14, 0x00,  // max
};

TEST(components_Health, serialization)
{
    std::uint8_t store[100];
    std::uint8_t *buffer = store;

    EXPECT_NO_THROW(TEST_DATA.serialize(buffer, sizeof(store)));
    EXPECT_EQ(buffer - store, Health::packedSize());
    EXPECT_EQ(::memcmp(store, SERIALIZED_TEST_DATA, Health::packedSize()), 0);
}

TEST(components_Health, deserialization)
{
    const std::uint8_t *buffer = SERIALIZED_TEST_DATA;
    Health data;

    EXPECT_NO_THROW(data = Health::deserialize(buffer, sizeof(SERIALIZED_TEST_DATA)));
    EXPECT_EQ(buffer - SERIALIZED_TEST_DATA, Health::packedSize());
    EXPECT_EQ(data.hp, TEST_DATA.hp);
    EXPECT_EQ(data.max, TEST_DATA.max);
}

TEST(components_Health, serializeAndDeserialize)
{
    Health initialData = { 65535, 65535 };
    Health deserializedData;
    std::uint8_t store[100];
    std::uint8_t *outputBuffer = store;
    const std::uint8_t *inputBuffer = store;

    EXPECT_NO_THROW(initialData.serialize(outputBuffer, sizeof(store)));
    EXPECT_NO_THROW(deserializedData = Health::deserialize(inputBuffer, sizeof(store)));
    EXPECT_EQ(initialData.hp, deserializedData.hp);
    EXPECT_EQ(initialData.max, deserializedData.max);
}

TEST(components_Health, smallBufferSerialize)
{
    std::uint8_t store[Health::packedSize() - 1];
    std::uint8_t* buffer = store;

    EXPECT_THROW(TEST_DATA.serialize(buffer, sizeof(store)), Protecs::SerializationError);
}

TEST(components_Health, smallBufferDeserialize)
{
    const std::uint8_t* buffer = SERIALIZED_TEST_DATA;

    EXPECT_THROW(Health::deserialize(buffer, sizeof(SERIALIZED_TEST_DATA) - 1), Protecs::SerializationError);
}

TEST(components_Health, isTheLastComponent)
{
    using Protecs::Components::Manager;

    EXPECT_EQ(Manager::index<Protecs::Components::PlayerName>() + 1, Manager::index<Health>());
}
