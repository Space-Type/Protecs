/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** PathFinding system
*/

#pragma once

#include <protecs/components.hpp>
#include <protecs/common.hpp>
#include <wrecks/ecs.hpp>
#include <functional>


namespace Protecs::Systems {
    class PathFinding {
        std::function<Components::PathFinding&(Wrecks::ECS::Entity entity)> m_GetPathFinding;
        std::function<Components::Velocity&(Wrecks::ECS::Entity entity)> m_GetVelocity;

        public:
            static constexpr Wrecks::ECS::SystemAttributes ATTRIBUTES = {
                .stage = Wrecks::ECS::SystemAttributes::FIXED_UPDATE,
                .order = 0
            };

        public:
            PathFinding() noexcept;

            static constexpr Signature signature() noexcept
            {
                return Signature()
                    .set(Components::Manager::index<Components::PathFinding>())
                    .set(Components::Manager::index<Components::Velocity>());
            }

            template <typename T>
            void setEngine(T* engine) noexcept
            {
                m_GetPathFinding = [=](Wrecks::ECS::Entity entity) noexcept -> Components::PathFinding& { return engine->template get<Components::PathFinding>()[entity]; };
                m_GetVelocity    = [=](Wrecks::ECS::Entity entity) noexcept -> Components::Velocity&    { return engine->template get<Components::Velocity>()[entity]; };
            }

            void operator()(Wrecks::ECS::Entity entity, Wrecks::DeltaTime dt);

        private:
            void straightPathFinding(Components::PathFinding& pathfinding, Components::Velocity& velocity);

            static float snapToDelta(float value, float targetValue) noexcept;
    };
}
