/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** Level component
*/

#pragma once

#include <cstdint>
#include <cstddef>


namespace Protecs::Components {
    struct Level {
        std::uint32_t progression;  // progresses linearly as the level advances
        std::uint8_t stage;

        void serialize(std::uint8_t*& output, std::size_t size) const;
        static Level deserialize(const std::uint8_t*& data, std::size_t size);

        /**
         * Returns the size (in bytes) of the
         * struct, without taking into account
         * any padding / alignment bytes the
         * compiler may add to it.
         */
        [[nodiscard]] static constexpr std::size_t packedSize()
        {
            return
                sizeof(progression) +
                sizeof(stage);
        }
    };
}
