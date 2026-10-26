/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Implementation for
** PlayerJoin packet
*/

#include "PlayerJoin.hpp"
#include <protecs/errors.hpp>
#include <protecs/utils.hpp>
#include <algorithm>


auto Protecs::Networking::Packets::PlayerJoin::fromStr(std::string_view name) -> PlayerJoin
{
    PlayerJoin data;

    name = name.substr(0, data.name.size());
    std::copy(name.begin(), name.end(), data.name.begin());
    data.length = name.length();

    return data;
}

auto Protecs::Networking::Packets::PlayerJoin::str() const -> std::string_view
{
    return std::string_view(name.data(), static_cast<std::size_t>(length));
}

void Protecs::Networking::Packets::PlayerJoin::serialize(std::span<std::uint8_t> output) const
{
    if (output.size() < packedSize())
        throw SerializationError("unable to serialize PlayerJoin packet as the output buffer is too small");

    auto* current = output.data();

    Utils::copyFromValue(current, length);
    current = std::copy_n(name.data(), length, current);
}

auto Protecs::Networking::Packets::PlayerJoin::deserialize(std::span<const std::uint8_t> input) -> PlayerJoin
{
    if (input.size() < sizeof(std::uint8_t))
        throw SerializationError("unable to deserialize PlayerJoin packet as the input buffer is too small");

    const auto* current = input.data();
    PlayerJoin result;

    Utils::copyToValue(result.length, current);
    if (input.size() - sizeof(std::uint8_t) < result.length)
        throw SerializationError("unable to deserialize PlayerJoin packet as the input buffer is too small");

    std::copy_n(current, result.length, result.name.data());
    current += result.length;

    return result;
}
