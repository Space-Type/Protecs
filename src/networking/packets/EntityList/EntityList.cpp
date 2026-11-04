/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Implementation for
** EntityList packet
*/

#include "EntityList.hpp"
#include <protecs/errors.hpp>
#include <protecs/utils.hpp>


void Protecs::Networking::Packets::EntityList::serialize(std::span<std::uint8_t> output) const
{
    if (output.size() < packedSize())
        throw SerializationError("unable to serialize EntityList packet as the output buffer is too small");

    auto* current = output.data();

    Utils::copyFromValue(current, simulationTick);
    Utils::copyFromValue(current, static_cast<std::uint32_t>(entities.size()));
    for (auto& [entity, signature] : entities) {
        Utils::copyFromValue(current, entity);
        Utils::copyFromValue(current, signature);
    }
}

auto Protecs::Networking::Packets::EntityList::deserialize(std::span<const std::uint8_t> input) -> EntityList
{
    if (input.size() < partialPackedSize())
        throw SerializationError("unable to deserialize EntityList packet as the input buffer is too small");

    EntityList result;
    std::uint32_t entityCount;

    const auto* current = input.data();

    Utils::copyToValue(result.simulationTick, current);
    Utils::copyToValue(entityCount, current);

    if (entityCount == 0)
        return result;

    if (input.size() - sizeof(std::uint32_t) < (sizeof(NetworkEntity) + sizeof(Signature)) * entityCount)
        throw SerializationError("unable to deserialize EntityList packet as the input buffer is too small");

    result.entities.reserve(entityCount);

    for (std::uint32_t i = 0; i < entityCount; i++) {
        std::pair<NetworkEntity, Signature> entity;
        Utils::copyToValue(entity.first, current);
        Utils::copyToValue(entity.second, current);
        result.entities.push_back(std::move(entity));
    }

    return result;
}

auto Protecs::Networking::Packets::EntityList::packedSize() const noexcept -> std::size_t
{
    return
        partialPackedSize() +
        entities.size() * (sizeof(NetworkEntity) + sizeof(Signature));
}
