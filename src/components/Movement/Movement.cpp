/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Implementation for
** Movement component
*/

#include "Movement.hpp"
#include <protecs/errors.hpp>
#include <protecs/utils.hpp>


/**
 * Serializes the struct's data into
 * the specified data buffer (if possible).
 */
void Protecs::Components::Movement::serialize(std::uint8_t*& output, std::size_t size) const
{
    if (size < Movement::packedSize())
        throw Protecs::SerializationError("not enough bytes in input to serialize Movement into output");

    Utils::copyFromValue(output, direction.x);
    Utils::copyFromValue(output, direction.y);
    Utils::copyFromValue(output, speed);
}

/**
 * Deserializes the given data into
 * a Movement component (if possible).
 */
auto Protecs::Components::Movement::deserialize(const std::uint8_t*& data, std::size_t size) -> Movement
{
    if (size < Movement::packedSize())
        throw Protecs::SerializationError("not enough bytes in input to deserialize data into Movement");

    Movement result;

    Utils::copyToValue(result.direction.x, data);
    Utils::copyToValue(result.direction.y, data);
    Utils::copyToValue(result.speed, data);

    return result;
}
