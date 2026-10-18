/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Windows implementation
** for Address struct
*/

#include "Address.hpp"
#include <protecs/errors.hpp>
#include <ws2tcpip.h>
#include <cstring>


auto Protecs::Networking::Address::construct(std::string_view host, std::uint16_t port) -> Address
{
    Address addr = {};

    addr.sin_family = AF_INET;
    addr.sin_port = ::htons(port);

    if (!::inet_pton(AF_INET, host.data(), &addr.sin_addr))
        throw NetworkError("invalid hostname: \"" + std::string(host) + "\"");

    return addr;
}

auto Protecs::Networking::Address::host() const noexcept -> std::string_view
{
    constexpr std::size_t hostSize = 16;  // 3x4 (numbers) + 3 (dots) + 1 ('\0')
    static char hostname[hostSize];

    std::fill_n(hostname, hostSize, '\0');
    const char* res = ::inet_ntop(AF_INET, &sin_addr, hostname, hostSize - 1);

    return res
        ? hostname
        : "<unknown host>";
}

auto Protecs::Networking::Address::port() const noexcept -> std::uint16_t
{
    return ::ntohs(sin_port);
}

bool Protecs::Networking::Address::operator==(const Address& other) const noexcept
{
    return std::memcmp(this, &other, sizeof(Address)) == 0;
}

std::ostream& operator<<(std::ostream& output, const Protecs::Networking::Address& addr)
{
    return output << addr.host() << ':' << addr.port();
}
