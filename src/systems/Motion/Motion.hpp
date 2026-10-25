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
#include <wrecks/ecs.hpp>
#include <functional>


namespace Protecs::Systems {
    class Motion {
        std::function<Components::Transform&(Wrecks::ECS::Entity entity)> m_GetTransform;
        std::function<Components::Velocity&(Wrecks::ECS::Entity entity)> m_GetVelocity;

        public:
            static constexpr Wrecks::ECS::SystemAttributes ATTRIBUTES = {
                .stage = Wrecks::ECS::SystemAttributes::FIXED_UPDATE,
                .order = 10  // give enough space for other systems
            };

        public:
            Motion() noexcept;

            static constexpr Signature signature() noexcept
            {
                return Signature()
                    .set(Components::Manager::index<Components::Transform>())
                    .set(Components::Manager::index<Components::Velocity>());
            }

            template <typename T>
            void setEngine(T* engine) noexcept
            {
                m_GetTransform = [=](Wrecks::ECS::Entity entity) noexcept -> Components::Transform& { return engine->template get<Components::Transform>()[entity]; };
                m_GetVelocity = [=](Wrecks::ECS::Entity entity) noexcept  -> Components::Velocity&{ return engine->template get<Components::Velocity>()[entity]; };
            }

            void operator()(Wrecks::ECS::Entity entity, Wrecks::DeltaTime dt);
    };
}
