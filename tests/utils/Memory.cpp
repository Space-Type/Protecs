/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Unit tests for
** Memory functions
*/

#include <gtest/gtest.h>
#include <protecs/utils.hpp>
#include <bitset>


TEST(utils_Memory, copyFromValueGeneric)
{
    std::uint8_t data[8];
    std::size_t value = 82;

    std::uint8_t* current = data;
    Protecs::Utils::copyFromValue(current, value);

    EXPECT_EQ(::memcmp(data, &value, sizeof(std::size_t)), 0);
    EXPECT_EQ(current, data + sizeof(std::size_t));
}

TEST(utils_Memory, copyToValueGeneric)
{
    std::uint8_t data[2] = { 255, 255 };
    std::uint16_t value = 5;

    const std::uint8_t* current = data;
    Protecs::Utils::copyToValue(value, current);

    EXPECT_EQ(value, 0xffff);
    EXPECT_EQ(current, data + sizeof(std::uint16_t));
}

TEST(utils_Memory, bitsetManips)
{
    std::uint8_t data[8];
    std::bitset<64> initialBits;
    std::bitset<64> finalBits;

    initialBits.set(14);
    initialBits.set(54);

    std::uint8_t* copyIntoPtr = data;
    Protecs::Utils::copyFromValue(copyIntoPtr, initialBits);

    const std::uint8_t* copyFromPtr = data;
    Protecs::Utils::copyToValue(finalBits, copyFromPtr);

    EXPECT_EQ(initialBits, finalBits);
}
