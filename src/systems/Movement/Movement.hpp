/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** Movement system
*/

#pragma once

#include <protecs/components.hpp>
#include <protecs/common.hpp>
#include <wrecks/ecs.hpp>
#include <functional>


namespace Protecs::Systems {
    class Movement {
        std::function<Components::Movement&(Wrecks::ECS::Entity entity)> m_GetMovement;
        std::function<Components::Velocity&(Wrecks::ECS::Entity entity)> m_GetVelocity;

        public:
            static constexpr Wrecks::ECS::SystemAttributes ATTRIBUTES = {
                .stage = Wrecks::ECS::SystemAttributes::FIXED_UPDATE,
                .order = 10
            };

        public:
            Movement() noexcept;

            static constexpr Signature signature() noexcept
            {
                return Signature()
                    .set(Components::Manager::index<Components::Movement>())
                    .set(Components::Manager::index<Components::Velocity>());
            }

            template <typename T>
            void setEngine(T* engine) noexcept
            {
                m_GetMovement = [=](Wrecks::ECS::Entity entity) noexcept -> Components::Movement& { return engine->template get<Components::Movement>()[entity]; };
                m_GetVelocity = [=](Wrecks::ECS::Entity entity) noexcept -> Components::Velocity& { return engine->template get<Components::Velocity>()[entity]; };
            }

            void operator()(Wrecks::ECS::Entity entity, Wrecks::DeltaTime dt);
    };
}
