/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** Memory utility functions
*/

#pragma once

#include <cstring>
#include <cstdint>
#include <bitset>


namespace Protecs::Utils {
    /**
     * Copies the specified value into
     * the destination via memcpy().
     * The given destination buffer is
     * then advanced to the first byte
     * after the copied value.
     */
    template <typename Dest, typename Val>
    inline void copyFromValue(Dest*& dest, const Val& value) noexcept
    {
        std::memcpy(dest, &value, sizeof(Val));
        *reinterpret_cast<char**>(&dest) += sizeof(Val);
    }

    /**
     * See documentation on copyFromValue()
     * above. This overload is specifically
     * for bitsets, which aren't guaranteed
     * to work with ::memcpy().
     */
    template <typename Dest, std::size_t N>
    inline void copyFromValue(Dest*& dest, const std::bitset<N>& value) noexcept
    {
        std::size_t bytes = (N + 7) / 8;
        std::fill_n(dest, bytes, 0);

        auto* byteDest = reinterpret_cast<std::uint8_t*>(dest);
        dest = reinterpret_cast<Dest*>(byteDest + bytes);

        for (std::size_t i = 0; i < N; i++) {
            if (!value[i])
                continue;

            byteDest[i / 8] |= static_cast<std::uint8_t>(1u << (i % 8));
        }
    }

    /**
     * Copies sizeof(Dest) bytes from
     * the given source to dest via
     * memcpy().
     * The given source pointer will
     * be advanced to the first byte
     * after the copied value.
     */
    template <typename Dest, typename Src>
    inline void copyToValue(Dest& dest, const Src*& src)
    {
        std::memcpy(&dest, src, sizeof(Dest));
        *reinterpret_cast<const char**>(&src) += sizeof(Dest);
    }

    /**
     * See documentation on copyToValue()
     * above. This overload is specifically
     * for bitsets, which aren't guaranteed
     * to work with ::memcpy().
     */
    template <std::size_t N, typename Src>
    inline void copyToValue(std::bitset<N>& dest, const Src*& src)
    {
        std::size_t bytes = (N + 7) / 8;

        auto* byteSrc = reinterpret_cast<const std::uint8_t*>(src);
        src = reinterpret_cast<const Src*>(byteSrc + bytes);

        for (std::size_t i = 0; i < N; i++) {
            dest[i] = (byteSrc[i / 8] >> (i % 8)) & 1u;
        }
    }
}
