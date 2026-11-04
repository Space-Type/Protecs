/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** PacketQueue class
*/

#pragma once

#include "../Packet/Packet.hpp"
#include <optional>
#include <vector>
#include <mutex>


namespace Protecs::Networking {
    /**
     * Packet container class.
     *
     * The purpose of this class is to act
     * as a self-sorting packet container.
     * Packets are sorted by priority, which
     * is determined by their simulation tick
     * (if applicable), amongst other parameters.
     *
     * This container is thread-safe.
     */
    class PacketQueue {
        std::vector<Packet> m_Buffer;
        mutable std::mutex m_BufferLock;

        public:
            constexpr PacketQueue() noexcept
                : m_Buffer()
                , m_BufferLock()  // may or may not be constexpr
            {}

            /**
             * Returns the first simulation
             * for which a packet has been received.
             */
            Tick firstTick() const;

            void push(Packets::PacketData&& data);
            void push(Packet&& packet);
            std::optional<Packet> pop();

        private:
            static bool hasHigherPriority(const Packet& a, const Packet& b) noexcept;
    };
}
