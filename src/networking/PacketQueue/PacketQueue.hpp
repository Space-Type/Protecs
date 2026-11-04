/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** PacketQueue class
*/

#pragma once

#include "../Address/Address.hpp"
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
        using Element = std::pair<Address, Packet>;

        std::vector<Element> m_Buffer;
        mutable std::mutex m_BufferLock;

        public:
            PacketQueue(PacketQueue&& other);
            constexpr PacketQueue() noexcept
                : m_Buffer()
                , m_BufferLock()  // may or may not be constexpr
            {}

            /**
             * Returns the first simulation
             * for which a packet has been received.
             */
            Tick firstTick() const;

            void push(const Address& addr, Packets::PacketData&& data);
            void push(const Address& addr, const Packet& packet);
            std::optional<Element> pop();

            void swap(PacketQueue& other);
            inline PacketQueue& operator=(PacketQueue&& other) { swap(other); return *this; }

        private:
            static bool hasHigherPriority(const Element& a, const Element& b) noexcept;
    };
}
