/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Implementation for
** Transform component
*/

#include "Transform.hpp"
#include <protecs/errors.hpp>
#include <protecs/utils.hpp>


/**
 * Serializes the struct's data into
 * the specified data buffer (if possible).
 */
void Protecs::Components::Transform::serialize(std::uint8_t*& output, std::size_t size) const
{
    if (size < Transform::packedSize())
        throw Protecs::SerializationError("not enough bytes in input to serialize Transform into output");

    Utils::copyFromValue(output, position.x);
    Utils::copyFromValue(output, position.y);
    Utils::copyFromValue(output, rotation);
    Utils::copyFromValue(output, scale);
}

/**
 * Deserializes the given data into
 * a transform component (if possible).
 */
auto Protecs::Components::Transform::deserialize(const std::uint8_t*& data, std::size_t size) -> Transform
{
    if (size < Transform::packedSize())
        throw Protecs::SerializationError("not enough bytes in input to deserialize data into Transform");

    Transform result;

    Utils::copyToValue(result.position.x, data);
    Utils::copyToValue(result.position.y, data);
    Utils::copyToValue(result.rotation, data);
    Utils::copyToValue(result.scale, data);

    return result;
}
