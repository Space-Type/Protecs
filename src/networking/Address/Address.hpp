/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** Address struct
*/

#pragma once

#include <cstdint>
#include <ostream>

// include sockaddr_in
#ifdef _WIN32
    #include <winsock2.h>
#else
    #include <netinet/in.h>
#endif

namespace Protecs::Networking {
    struct Address : sockaddr_in {
        static Address construct(std::string_view host, std::uint16_t port);

        [[nodiscard]] std::string_view host() const noexcept;
        [[nodiscard]] std::uint16_t port() const noexcept;

        bool operator==(const Address& other) const noexcept;
        inline bool operator!=(const Address& other) const noexcept { return !(*this == other); }
    };
}

std::ostream& operator<<(std::ostream& output, const Protecs::Networking::Address& addr);

template <>
struct std::hash<Protecs::Networking::Address>{
    static inline std::size_t operator()(const Protecs::Networking::Address& addr)
    {
        std::string_view repr(reinterpret_cast<const char*>(&addr), sizeof(Protecs::Networking::Address));
        return std::hash<std::string_view>{}(repr);
    }
};
