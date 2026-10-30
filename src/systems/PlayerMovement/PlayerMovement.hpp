/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** PlayerMovement system
*/

#pragma once

#include <protecs/components.hpp>
#include <protecs/common.hpp>
#include <wrecks/ecs.hpp>
#include <functional>


namespace Protecs::Systems {
    class PlayerMovement {
        std::function<Components::PlayerInput&(Wrecks::ECS::Entity entity)> m_GetPlayerInput;
        std::function<Components::Movement&(Wrecks::ECS::Entity entity)> m_GetMovement;

        public:
            static constexpr Wrecks::ECS::SystemAttributes ATTRIBUTES = {
                .stage = Wrecks::ECS::SystemAttributes::FIXED_UPDATE,
                .order = 10
            };

        public:
            PlayerMovement() noexcept;

            static constexpr Signature signature() noexcept
            {
                return Signature()
                    .set(Components::Manager::index<Components::PlayerInput>())
                    .set(Components::Manager::index<Components::Movement>());
            }

            template <typename T>
            void setEngine(T* engine) noexcept
            {
                m_GetPlayerInput = [=](Wrecks::ECS::Entity entity) noexcept -> Components::PlayerInput& { return engine->template get<Components::PlayerInput>()[entity]; };
                m_GetMovement    = [=](Wrecks::ECS::Entity entity) noexcept -> Components::Movement&    { return engine->template get<Components::Movement>()[entity]; };
            }

            void operator()(Wrecks::ECS::Entity entity, Wrecks::DeltaTime dt);
    };
}
