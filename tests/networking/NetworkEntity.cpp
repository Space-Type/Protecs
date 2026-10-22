/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Unit tests for
** NetworkEntity functions
*/

#include <gtest/gtest.h>
#include <protecs.hpp>
#include <thread>
#include <chrono>


using Protecs::Networking::generateNetworkEntity;
using std::chrono_literals::operator ""ms;


TEST(networking_NetworkEntity, uniqueWithSimilarInput)
{
    auto entity1 = generateNetworkEntity(52);
    auto entity2 = generateNetworkEntity(53);

    EXPECT_NE(entity1, entity2);
}

TEST(networking_NetworkEntity, uniqueWithSameInput)
{
    auto entity1 = generateNetworkEntity(52);
    std::this_thread::sleep_for(1ms);  // not necessary, but improves test stability
    auto entity2 = generateNetworkEntity(52);

    EXPECT_NE(entity1, entity2);
}
