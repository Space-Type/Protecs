/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Implementation for
** Velocity component
*/

#include "Velocity.hpp"
#include <protecs/errors.hpp>
#include <protecs/utils.hpp>


/**
 * Serializes the struct's data into
 * the specified data buffer (if possible).
 */
void Protecs::Components::Velocity::serialize(std::uint8_t*& output, std::size_t size) const
{
    if (size < Velocity::packedSize())
        throw Protecs::SerializationError("not enough bytes in input to serialize Velocity into output");

    Utils::copyFromValue(output, position.x);
    Utils::copyFromValue(output, position.y);
    Utils::copyFromValue(output, angular);
}

/**
 * Deserializes the given data into
 * a Velocity component (if possible).
 */
auto Protecs::Components::Velocity::deserialize(const std::uint8_t*& data, std::size_t size) -> Velocity
{
    if (size < Velocity::packedSize())
        throw Protecs::SerializationError("not enough bytes in input to deserialize data into Velocity");

    Velocity result;

    Utils::copyToValue(result.position.x, data);
    Utils::copyToValue(result.position.y, data);
    Utils::copyToValue(result.angular, data);

    return result;
}
