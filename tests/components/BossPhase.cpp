/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Unit tests for
** BossPhase component
*/

#include <gtest/gtest.h>
#include <protecs/components.hpp>
#include <protecs/errors.hpp>
#include <cstring>

using Protecs::Components::BossPhase;


static constexpr BossPhase TEST_DATA = { 2 };
static constexpr std::uint8_t SERIALIZED_TEST_DATA[] = {
    0x02,  // phase
};

TEST(components_BossPhase, serialization)
{
    std::uint8_t store[100];
    std::uint8_t *buffer = store;

    EXPECT_NO_THROW(TEST_DATA.serialize(buffer, sizeof(store)));
    EXPECT_EQ(buffer - store, BossPhase::packedSize());
    EXPECT_EQ(::memcmp(store, SERIALIZED_TEST_DATA, BossPhase::packedSize()), 0);
}

TEST(components_BossPhase, deserialization)
{
    const std::uint8_t *buffer = SERIALIZED_TEST_DATA;
    BossPhase data;

    EXPECT_NO_THROW(data = BossPhase::deserialize(buffer, sizeof(SERIALIZED_TEST_DATA)));
    EXPECT_EQ(buffer - SERIALIZED_TEST_DATA, BossPhase::packedSize());
    EXPECT_EQ(data.phase, TEST_DATA.phase);
}

TEST(components_BossPhase, startsAtPhaseOne)
{
    EXPECT_EQ(BossPhase{}.phase, 1);
}

TEST(components_BossPhase, smallBufferSerialize)
{
    std::uint8_t* buffer = nullptr;

    EXPECT_THROW(TEST_DATA.serialize(buffer, 0), Protecs::SerializationError);
}

TEST(components_BossPhase, smallBufferDeserialize)
{
    const std::uint8_t* buffer = SERIALIZED_TEST_DATA;

    EXPECT_THROW(BossPhase::deserialize(buffer, 0), Protecs::SerializationError);
}

TEST(components_BossPhase, isTheLastComponent)
{
    using Protecs::Components::Manager;

    EXPECT_EQ(Manager::index<Protecs::Components::Health>() + 1, Manager::index<BossPhase>());
}
