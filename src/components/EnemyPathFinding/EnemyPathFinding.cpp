/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Implementation for
** EnemyPathFinding component
*/

#include "EnemyPathFinding.hpp"
#include <protecs/errors.hpp>
#include <protecs/utils.hpp>


/**
 * Serializes the struct's data into
 * the specified data buffer (if possible).
 */
void Protecs::Components::EnemyPathFinding::serialize(std::uint8_t*& output, std::size_t size) const
{
    if (size < EnemyPathFinding::packedSize())
        throw Protecs::SerializationError("not enough bytes in input to serialize EnemyPathFinding into output");

    Utils::copyFromValue(output, type);
}

/**
 * Deserializes the given data into
 * a EnemyPathFinding component (if possible).
 */
auto Protecs::Components::EnemyPathFinding::deserialize(const std::uint8_t*& data, std::size_t size) -> EnemyPathFinding
{
    if (size < EnemyPathFinding::packedSize())
        throw Protecs::SerializationError("not enough bytes in input to deserialize data into EnemyPathFinding");

    EnemyPathFinding result;
    Utils::copyToValue(result.type, data);
    return result;
}
