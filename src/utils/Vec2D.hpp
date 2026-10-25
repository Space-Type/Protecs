/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** 2D vector implementation
*/

#pragma once

#include <type_traits>
#include <algorithm>
#include <cmath>


namespace Protecs::Utils {
    template <typename T>
    concept NumberType =
        std::is_floating_point<T>::value ||
        std::is_integral<T>::value;

    template <NumberType T>
    struct Vec2D {
        using Num = T;

        static const Vec2D UP;
        static const Vec2D DOWN;
        static const Vec2D LEFT;
        static const Vec2D RIGHT;
        static const Vec2D ZERO;

        static constexpr Num NEAR_ZERO = 0.0000001;

        Num x;
        Num y;

        [[ nodiscard ]] constexpr bool null() const noexcept requires (std::is_integral_v<Num>) { return x == 0 && y == 0; }
        [[ nodiscard ]] constexpr bool null() const noexcept
            requires (std::is_floating_point_v<Num>)
        {
            return
                (-NEAR_ZERO < x && x < NEAR_ZERO) &&
                (-NEAR_ZERO < y && y < NEAR_ZERO);
        }

        [[ nodiscard ]] constexpr double sqrMagnitude() const
        {
            return
                static_cast<double>(x) * static_cast<double>(x) +
                static_cast<double>(y) * static_cast<double>(y);
        }

        [[ nodiscard ]] double magnitude() const { return std::sqrt(sqrMagnitude()); }

        template <NumberType OT>
        [[ nodiscard ]] constexpr double sqrDistance(const Vec2D<OT>& other) noexcept
        {
            double xDiff = static_cast<double>(x) - static_cast<double>(other.x);
            double yDiff = static_cast<double>(y) - static_cast<double>(other.y);

            return xDiff * xDiff + yDiff * yDiff;
        }

        template <NumberType OT>
        [[ nodiscard ]] double distance(const Vec2D<OT>& other) noexcept { return std::sqrt(sqrDistance(other)); }

        [[ nodiscard ]] Vec2D normalized() const { return Vec2D(*this).normalize(); }
        Vec2D& normalize() noexcept
        {
            if (null()) return *this;  // null vector is already normalized
            return *this /= magnitude();
        }

        template <NumberType OT1, NumberType OT2>
        [[ nodiscard ]] constexpr Vec2D clamped(const Vec2D<OT1>& min, const Vec2D<OT2>& max) noexcept { return Vec2D(*this).clamp(min, max); }

        /**
         * Component-wise clamping function.
         */
        template <NumberType OT1, NumberType OT2>
        constexpr Vec2D& clamp(const Vec2D<OT1>& min, const Vec2D<OT2>& max) noexcept
        {
           x = std::clamp(x, static_cast<Num>(min.x), static_cast<Num>(max.x));
           y = std::clamp(y, static_cast<Num>(min.y), static_cast<Num>(max.y));
           return *this;
        }

        template <NumberType OT>
        [[ nodiscard ]] constexpr Vec2D operator+(const Vec2D<OT>& other) const noexcept { return Vec2D(*this) += other; }

        template <NumberType OT>
        constexpr Vec2D& operator+=(const Vec2D<OT>& other) noexcept
        {
            x += static_cast<Num>(other.x);
            y += static_cast<Num>(other.y);
            return *this;
        }

        template <NumberType OT>
        [[ nodiscard ]] constexpr Vec2D operator-(const Vec2D<OT>& other) const noexcept { return Vec2D(*this) -= other; }

        template <NumberType OT>
        constexpr Vec2D& operator-=(const Vec2D<OT>& other) noexcept
        {
            x -= static_cast<Num>(other.x);
            y -= static_cast<Num>(other.y);
            return *this;
        }

        [[ nodiscard ]] constexpr Vec2D operator*(Num factor) const noexcept { return Vec2D(*this) *= factor; }
        constexpr Vec2D& operator*=(Num factor) noexcept
        {
            x *= factor;
            y *= factor;
            return *this;
        }

        [[ nodiscard ]] constexpr Vec2D operator/(Num factor) const noexcept { return Vec2D(*this) /= factor; }
        constexpr Vec2D& operator/=(Num factor) noexcept
        {
            x /= factor;
            y /= factor;
            return *this;
        }

        template <NumberType OT>
        constexpr void operator=(const Vec2D<OT>& other)
        {
            x = static_cast<Num>(other.x);
            y = static_cast<Num>(other.y);
        }

        template <NumberType OT>
        constexpr bool operator==(const Vec2D<OT>& other) const noexcept { return !(*this != other); }

        template <NumberType OT>
        constexpr bool operator!=(const Vec2D<OT>& other) const noexcept
        {
            return
                (x != static_cast<Num>(other.x)) ||
                (y != static_cast<Num>(other.y));
        }

        template <NumberType OT>
        constexpr operator Vec2D<OT>() const
        {
            return {
                static_cast<OT>(x),
                static_cast<OT>(y),
            };
        }
    };

    template <NumberType T>
    inline constexpr Vec2D<T> Vec2D<T>::UP    = {  0, -1 };  // y axis inverted for screens

    template <NumberType T>
    inline constexpr Vec2D<T> Vec2D<T>::DOWN  = {  0,  1 };

    template <NumberType T>
    inline constexpr Vec2D<T> Vec2D<T>::LEFT  = { -1,  0 };

    template <NumberType T>
    inline constexpr Vec2D<T> Vec2D<T>::RIGHT = {  1,  0 };

    template <NumberType T>
    inline constexpr Vec2D<T> Vec2D<T>::ZERO  = {  0,  0 };
}
