/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** Motion system
*/

#pragma once

#include <protecs/components.hpp>
#include <protecs/common.hpp>
#include <algorithm>


namespace Protecs::Systems {
    template <typename T>
    class Motion {
        static constexpr float FRICTION_FACTOR_X = 0.90;
        static constexpr float FRICTION_FACTOR_Y = FRICTION_FACTOR_X;

        T* m_Engine;

        public:
            static constexpr Wrecks::ECS::SystemAttributes ATTRIBUTES = { .stage = Wrecks::ECS::SystemAttributes::STATE };

        public:
            Motion() noexcept;

            static constexpr Signature signature() noexcept
            {
                return Signature()
                    .set(Components::Manager::index<Components::Transform>())
                    .set(Components::Manager::index<Components::Velocity>());
            }

            inline void setEngine(T* engine) noexcept { m_Engine = engine; }

            void operator()(Entity entity)
            {
                auto& velocity = m_Engine->template get<Components::Velocity>()[entity];
                auto& transforms = m_Engine->template get<Components::Transform>()[entity];

                transforms.x = std::clamp(transforms.x + velocity.velocityX, 0.f, POSITION_MAX_X);
                transforms.y = std::clamp(transforms.y + velocity.velocityY, 0.f, POSITION_MAX_Y);

                velocity.velocityX *= FRICTION_FACTOR_X;
                velocity.velocityY *= FRICTION_FACTOR_Y;
            }
    };
}
