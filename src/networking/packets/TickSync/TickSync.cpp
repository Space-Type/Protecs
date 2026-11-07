/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Implementation for
** TickSync packet
*/

#include "TickSync.hpp"
#include <chrono>
#include <protecs/errors.hpp>
#include <protecs/utils.hpp>


void Protecs::Networking::Packets::TickSync::serialize(std::span<std::uint8_t> output) const
{
    if (output.size() < packedSize())
        throw SerializationError("unable to serialize TickSync packet as the output buffer is too small");

    auto* current = output.data();

    Utils::copyFromValue(current, clientTick);
    Utils::copyFromValue(current, serverTick);
    Utils::copyFromValue(current, clientTime.time_since_epoch());
    Utils::copyFromValue(current, serverTime.time_since_epoch());
}

auto Protecs::Networking::Packets::TickSync::deserialize(std::span<const std::uint8_t> input) -> TickSync
{
    if (input.size() < packedSize())
        throw SerializationError("unable to deserialize TickSync packet as the input buffer is too small");

    const auto* current = input.data();
    std::chrono::steady_clock::time_point::duration clientTime;
    std::chrono::steady_clock::time_point::duration serverTime;
    TickSync result;

    Utils::copyToValue(result.clientTick, current);
    Utils::copyToValue(result.serverTick, current);
    Utils::copyToValue(clientTime, current);
    Utils::copyToValue(serverTime, current);

    result.clientTime = std::chrono::steady_clock::time_point(clientTime);
    result.serverTime = std::chrono::steady_clock::time_point(serverTime);

    return result;
}
