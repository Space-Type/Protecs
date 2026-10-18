/*
** EPITECH PROJECT, 2026
** Project - Wrecks
** File description:
** Linux implementation for
** UDPSocket class
*/

#include "UDPSocket.hpp"
#include <protecs/errors.hpp>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <sys/socket.h>
#include <arpa/inet.h>


Protecs::Networking::UDPSocket::UDPSocket(std::string_view host, std::uint16_t port)
    : UDPSocket()
{
    open(host, port);
}

Protecs::Networking::UDPSocket::UDPSocket(UDPSocket&& other) noexcept
    : UDPSocket()
{
    swap(other);
}

Protecs::Networking::UDPSocket::UDPSocket() noexcept
    : m_Address{ 0 }
    , m_FD(-1)
{
}

Protecs::Networking::UDPSocket::~UDPSocket()
{
    close();
}

void Protecs::Networking::UDPSocket::open(std::string_view host, std::uint16_t port)
{
    m_FD = ::socket(AF_INET, SOCK_DGRAM, 0);
    if (m_FD < 0)
        throw NetworkError::fromErrno();

    m_Address = Address::construct(host, port);

    int status = ::bind(m_FD, reinterpret_cast<sockaddr*>(&m_Address), sizeof(m_Address));
    if (status < 0)
        throw NetworkError::fromErrno();
}

void Protecs::Networking::UDPSocket::close() noexcept
{
    if (m_FD < 0)
        return;  // not necessary but might help speed up

    ::close(m_FD);

    m_Address = { 0 };
    m_FD = -1;
}

bool Protecs::Networking::UDPSocket::isOpen() const noexcept
{
    return m_FD >= 0;
}

void Protecs::Networking::UDPSocket::setNonBlocking(bool setting)
{
    int flags = ::fcntl(m_FD, F_GETFL, 0);

    if (setting)
        ::fcntl(m_FD, F_SETFL, flags | O_NONBLOCK);
    else
        ::fcntl(m_FD, F_SETFL, flags & ~O_NONBLOCK);
}

bool Protecs::Networking::UDPSocket::pollReceive(int timeout) const
{
    pollfd fd = { m_FD, POLLIN, 0 };
    ::poll(&fd, 1, timeout);
    return fd.revents & POLLIN;
}

void Protecs::Networking::UDPSocket::swap(UDPSocket& other) noexcept
{
    std::swap(m_Address, other.m_Address);
    std::swap(m_FD, other.m_FD);
}

bool Protecs::Networking::UDPSocket::sendBytes(const char* data, std::size_t length, const Address& addr) noexcept
{
    auto bytesSent = ::sendto(
        m_FD,
        data, length,
        0,
        reinterpret_cast<const sockaddr*>(&addr),
        sizeof(Address)
    );

    if (bytesSent < 0)
        close();

    return bytesSent >= 0 && bytesSent == length;
}

size_t Protecs::Networking::UDPSocket::receiveBytes(char* data, std::size_t size, Address* dest) noexcept
{
    socklen_t addrLen = sizeof(Address);

    auto bytesReceived = ::recvfrom(
        m_FD,
        data, size,
        0,
        reinterpret_cast<sockaddr*>(dest),
        dest ? &addrLen : nullptr
    );

    if (bytesReceived < 0) {
        close();
        return 0;
    }

    return static_cast<size_t>(bytesReceived);
}
