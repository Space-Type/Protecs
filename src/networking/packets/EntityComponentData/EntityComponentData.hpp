/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** EntityComponentData packet
*/

#pragma once

#include <protecs/common.hpp>
#include <protecs/components.hpp>
#include <cstdint>
#include <span>


namespace Protecs::Networking::Packets {
    struct EntityComponentData {
        Entity entity;
        Components::Variant component;

        void serialize(std::span<std::uint8_t> output) const;
        static EntityComponentData deserialize(std::span<const std::uint8_t> input);

        [[nodiscard]] std::size_t packedSize() const noexcept;
    };
}
