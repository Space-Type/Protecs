/*
** EPITECH PROJECT, 2026
** Project - Wrecks
** File description:
** Windows implementation for
** UDPSocket class
*/

#include "UDPSocket.hpp"
#include <protecs/errors.hpp>
#include <winsock2.h>
#include <ws2tcpip.h>


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
    , m_Socket(INVALID_SOCKET)
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);  // FIXME: this works but it's bad
}

Protecs::Networking::UDPSocket::~UDPSocket()
{
    WSACleanup();
    close();
}

void Protecs::Networking::UDPSocket::open(std::string_view host, std::uint16_t port)
{
    m_Socket = ::socket(AF_INET, SOCK_DGRAM, 0);
    if (m_Socket == INVALID_SOCKET)
        throw NetworkError("failed to open socket");  // TODO: replace with ::fromErrno

    m_Address = Address::construct(host, port);

    int status = ::bind(m_Socket, reinterpret_cast<const sockaddr*>(&m_Address), sizeof(m_Address));
    if (status != 0)
        throw NetworkError("failed to bind");  // TODO: replace with ::fromErrno
}

void Protecs::Networking::UDPSocket::close() noexcept
{
    if (m_Socket == INVALID_SOCKET)
        return;

    ::closesocket(m_Socket);

    m_Address = {};
    m_Socket = INVALID_SOCKET;
}

bool Protecs::Networking::UDPSocket::isOpen() const noexcept
{
    return m_Socket != INVALID_SOCKET;
}

void Protecs::Networking::UDPSocket::setNonBlocking(bool setting)
{
    unsigned long enabled = setting;
    int success = ::ioctlsocket(m_Socket, FIONBIO, &enabled);

    if (success != 0)
        throw NetworkError("failed to change socket blocking mode");  // TODO: set ::fromErrno
}

bool Protecs::Networking::UDPSocket::pollReceive(int timeout) const
{
    WSAPOLLFD pollfds = { m_Socket, POLLIN, 0 };
    WSAPoll(&pollfds, 1, timeout);
    return pollfds.revents & POLLIN;
}

void Protecs::Networking::UDPSocket::swap(UDPSocket& other) noexcept
{
    std::swap(m_Address, other.m_Address);
    std::swap(m_Socket, other.m_Socket);
}

bool Protecs::Networking::UDPSocket::sendBytes(const char* data, std::size_t length, const Address& dest) noexcept
{
    int bytesSent = ::sendto(m_Socket, data, static_cast<int>(length), 0, reinterpret_cast<const sockaddr*>(&dest), sizeof(Address));

    if (bytesSent == SOCKET_ERROR)
        close();

    return bytesSent > 0 && static_cast<std::size_t>(bytesSent) == length;
}

size_t Protecs::Networking::UDPSocket::receiveBytes(char* data, std::size_t size, Address* dest) noexcept
{
    socklen_t addrLen = sizeof(Address);
    int bytesReceived = ::recvfrom(m_Socket, data, size, 0, reinterpret_cast<sockaddr*>(dest), dest ? &addrLen : nullptr);

    if (bytesReceived == SOCKET_ERROR)
        close();

    return static_cast<std::size_t>(bytesReceived < 0 ? 0 : bytesReceived);
}
