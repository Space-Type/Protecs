/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Implementation for
** Health component
*/

#include "Health.hpp"
#include <protecs/errors.hpp>
#include <protecs/utils.hpp>


/**
 * Serializes the struct's data into
 * the specified data buffer (if possible).
 */
void Protecs::Components::Health::serialize(std::uint8_t*& output, std::size_t size) const
{
    if (size < Health::packedSize())
        throw Protecs::SerializationError("not enough bytes in input to serialize Health into output");

    Utils::copyFromValue(output, hp);
    Utils::copyFromValue(output, max);
}

/**
 * Deserializes the given data into
 * a Health component (if possible).
 */
auto Protecs::Components::Health::deserialize(const std::uint8_t*& data, std::size_t size) -> Health
{
    if (size < Health::packedSize())
        throw Protecs::SerializationError("not enough bytes in input to deserialize data into Health");

    Health result;

    Utils::copyToValue(result.hp, data);
    Utils::copyToValue(result.max, data);
    return result;
}
