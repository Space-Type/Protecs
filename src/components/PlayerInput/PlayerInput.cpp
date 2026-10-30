/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Implementation for
** PlayerInput component
*/

#include "PlayerInput.hpp"
#include <protecs/errors.hpp>
#include <protecs/utils.hpp>


/**
 * Serializes the struct's data into
 * the specified data buffer (if possible).
 */
void Protecs::Components::PlayerInput::serialize(std::uint8_t*& output, std::size_t size) const
{
    if (size < PlayerInput::packedSize())
        throw Protecs::SerializationError("not enough bytes in input to serialize PlayerInput into output");

    Utils::copyFromValue(output, packed());
}

/**
 * Deserializes the given data into
 * a PlayerInput component (if possible).
 */
auto Protecs::Components::PlayerInput::deserialize(const std::uint8_t*& data, std::size_t size) -> PlayerInput
{
    if (size < PlayerInput::packedSize())
        throw Protecs::SerializationError("not enough bytes in input to deserialize data into PlayerInput");

    std::uint8_t packed;
    Utils::copyToValue(packed, data);

    PlayerInput result;

    result.up      = packed & 0b10000;
    result.down    = packed & 0b01000;
    result.left    = packed & 0b00100;
    result.right   = packed & 0b00010;
    result.trigger = packed & 0b00001;

    return result;
}
