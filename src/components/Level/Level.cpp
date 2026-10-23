/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Implementation for
** Level component
*/

#include "Level.hpp"
#include <protecs/errors.hpp>
#include <protecs/utils.hpp>


/**
 * Serializes the struct's data into
 * the specified data buffer (if possible).
 */
void Protecs::Components::Level::serialize(std::uint8_t*& output, std::size_t size) const
{
    if (size < Level::packedSize())
        throw Protecs::SerializationError("not enough bytes in input to serialize Level into output");

    Utils::copyFromValue(output, progression);
    Utils::copyFromValue(output, stage);
}

/**
 * Deserializes the given data into
 * a Level component (if possible).
 */
auto Protecs::Components::Level::deserialize(const std::uint8_t*& data, std::size_t size) -> Level
{
    if (size < Level::packedSize())
        throw Protecs::SerializationError("not enough bytes in input to deserialize data into Level");

    Level result;

    Utils::copyToValue(result.progression, data);
    Utils::copyToValue(result.stage, data);

    return result;
}
