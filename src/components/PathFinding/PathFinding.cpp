/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Implementation for
** PathFinding component
*/

#include "PathFinding.hpp"
#include <protecs/errors.hpp>
#include <protecs/utils.hpp>


/**
 * Serializes the struct's data into
 * the specified data buffer (if possible).
 */
void Protecs::Components::PathFinding::serialize(std::uint8_t*& output, std::size_t size) const
{
    if (size < PathFinding::packedSize())
        throw Protecs::SerializationError("not enough bytes in input to serialize PathFinding into output");

    Utils::copyFromValue(output, type);
    Utils::copyFromValue(output, targetVelocity.x);
    Utils::copyFromValue(output, targetVelocity.y);
    Utils::copyFromValue(output, acceleration);
}

/**
 * Deserializes the given data into
 * a PathFinding component (if possible).
 */
auto Protecs::Components::PathFinding::deserialize(const std::uint8_t*& data, std::size_t size) -> PathFinding
{
    if (size < PathFinding::packedSize())
        throw Protecs::SerializationError("not enough bytes in input to deserialize data into PathFinding");

    PathFinding result;
    Utils::copyToValue(result.type, data);
    Utils::copyToValue(result.targetVelocity.x, data);
    Utils::copyToValue(result.targetVelocity.y, data);
    Utils::copyToValue(result.acceleration, data);
    return result;
}
