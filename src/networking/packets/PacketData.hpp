/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** PacketData variant
*/

#pragma once

#include <protecs/networking/packets.hpp>
#include <variant>


namespace Protecs::Networking::Packets {
    using PacketData = std::variant<EntityAddComponent,
                                    EntityComponentData,
                                    EntityCreate,
                                    EntityDelete,
                                    EntityRemoveComponent,
                                    EntitySyncComponents,
                                    Ping,
                                    PlayerId,
                                    PlayerInput,
                                    PlayerJoin,
                                    PlayerLeave>;
}
