/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Implementation for
** NetworkEntity functions
*/

#include "NetworkEntity.hpp"
#include <chrono>


static constexpr std::uint64_t UPPER_32_BITS = 0xffffffff00000000;


/**
 * Generates a unique network
 * entity from the given ECS
 * entity.
 */
auto Protecs::Networking::generateNetworkEntity(Wrecks::ECS::Entity entity) -> NetworkEntity
{
    auto time = std::chrono::steady_clock::now().time_since_epoch().count();
    NetworkEntity timePart = (time << (32 - 4)) & UPPER_32_BITS;

    return timePart | entity;
}
