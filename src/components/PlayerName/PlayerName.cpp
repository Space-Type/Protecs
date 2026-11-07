/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Implementation for
** PlayerName component
*/

#include "PlayerName.hpp"
#include <protecs/errors.hpp>
#include <protecs/utils.hpp>
#include <algorithm>


auto Protecs::Components::PlayerName::fromStr(std::string_view name) -> PlayerName
{
    PlayerName result;

    name = name.substr(0, MAX_LENGTH);
    std::copy(name.begin(), name.end(), result.name.begin());
    result.length = static_cast<std::uint8_t>(name.length());

    return result;
}

auto Protecs::Components::PlayerName::str() const -> std::string_view
{
    return std::string_view(name.data(), std::min<std::size_t>(length, MAX_LENGTH));
}

/**
 * Serializes the struct's data into
 * the specified data buffer (if possible).
 */
void Protecs::Components::PlayerName::serialize(std::uint8_t*& output, std::size_t size) const
{
    if (length > MAX_LENGTH)
        throw Protecs::SerializationError("PlayerName is longer than its maximum length");
    if (size < packedSize())
        throw Protecs::SerializationError("not enough bytes in input to serialize PlayerName into output");

    Utils::copyFromValue(output, length);
    output = std::copy_n(name.data(), length, output);
}

/**
 * Deserializes the given data into
 * a PlayerName component (if possible).
 */
auto Protecs::Components::PlayerName::deserialize(const std::uint8_t*& data, std::size_t size) -> PlayerName
{
    if (size < sizeof(std::uint8_t))
        throw Protecs::SerializationError("not enough bytes in input to deserialize data into PlayerName");

    PlayerName result;

    Utils::copyToValue(result.length, data);
    if (result.length > MAX_LENGTH)
        throw Protecs::SerializationError("PlayerName is longer than its maximum length");
    if (size - sizeof(std::uint8_t) < result.length)
        throw Protecs::SerializationError("not enough bytes in input to deserialize data into PlayerName");

    std::copy_n(data, result.length, result.name.data());
    data += result.length;

    return result;
}
