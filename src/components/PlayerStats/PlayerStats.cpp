/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Implementation for
** PlayerStats component
*/

#include "PlayerStats.hpp"
#include <protecs/errors.hpp>
#include <protecs/utils.hpp>


/**
 * Serializes the struct's data into
 * the specified data buffer (if possible).
 */
void Protecs::Components::PlayerStats::serialize(std::uint8_t*& output, std::size_t size) const
{
    if (size < PlayerStats::packedSize())
        throw Protecs::SerializationError("not enough bytes in input to serialize PlayerStats into output");

    Utils::copyFromValue(output, slot);
    Utils::copyFromValue(output, lives);
    Utils::copyFromValue(output, score);
}

/**
 * Deserializes the given data into
 * a PlayerStats component (if possible).
 */
auto Protecs::Components::PlayerStats::deserialize(const std::uint8_t*& data, std::size_t size) -> PlayerStats
{
    if (size < PlayerStats::packedSize())
        throw Protecs::SerializationError("not enough bytes in input to deserialize data into PlayerStats");

    PlayerStats result;

    Utils::copyToValue(result.slot, data);
    Utils::copyToValue(result.lives, data);
    Utils::copyToValue(result.score, data);
    return result;
}
