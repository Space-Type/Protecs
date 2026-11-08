/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Implementation for
** BossPhase component
*/

#include "BossPhase.hpp"
#include <protecs/errors.hpp>
#include <protecs/utils.hpp>


/**
 * Serializes the struct's data into
 * the specified data buffer (if possible).
 */
void Protecs::Components::BossPhase::serialize(std::uint8_t*& output, std::size_t size) const
{
    if (size < BossPhase::packedSize())
        throw Protecs::SerializationError("not enough bytes in input to serialize BossPhase into output");

    Utils::copyFromValue(output, phase);
}

/**
 * Deserializes the given data into
 * a BossPhase component (if possible).
 */
auto Protecs::Components::BossPhase::deserialize(const std::uint8_t*& data, std::size_t size) -> BossPhase
{
    if (size < BossPhase::packedSize())
        throw Protecs::SerializationError("not enough bytes in input to deserialize data into BossPhase");

    BossPhase result;

    Utils::copyToValue(result.phase, data);
    return result;
}
