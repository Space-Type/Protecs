/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** PlayerBounds system
*/

#pragma once

#include <protecs/components.hpp>
#include <protecs/common.hpp>
#include <wrecks/ecs.hpp>
#include <functional>


namespace Protecs::Systems {
    class PlayerBounds {
        std::function<Components::Transform&(Wrecks::ECS::Entity entity)> m_GetTransform;

        public:
            static constexpr Wrecks::ECS::SystemAttributes ATTRIBUTES = {
                .stage = Wrecks::ECS::SystemAttributes::FIXED_UPDATE,
                .order = 100
            };

        public:
            PlayerBounds() noexcept;

            static constexpr Signature signature() noexcept
            {
                return Signature()
                    .set(Components::Manager::index<Components::PlayerInput>())
                    .set(Components::Manager::index<Components::Transform>());
            }

            template <typename T>
            void setEngine(T* engine) noexcept
            {
                m_GetTransform = [=](Wrecks::ECS::Entity entity) noexcept -> Components::Transform& { return engine->template get<Components::Transform>()[entity]; };
            }

            void operator()(Wrecks::ECS::Entity entity, Wrecks::DeltaTime dt);
    };
}
