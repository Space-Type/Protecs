/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** Motion system
*/

#pragma once

#include <protecs/common.hpp>
#include <protecs/components.hpp>


namespace Protecs::Systems {
    class Motion {
        void* m_Engine;

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

            inline void setEngine(void* engine) noexcept { m_Engine = engine; }

            void operator()(Entity entity);
    };
}
