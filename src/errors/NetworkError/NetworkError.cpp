/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Implementation for
** NetworkError class
*/

#include "NetworkError.hpp"

#ifndef _WIN32
    #include <cstring>
    #include <cerrno>
#endif

Protecs::NetworkError::NetworkError(std::string_view msg)
    : Error(msg)
{

}

auto Protecs::NetworkError::fromErrno() -> NetworkError {
    #ifdef _WIN32
        // FIXME: implement for windows (if possible)
        return NetworkError("network error");
    #else
        return NetworkError(::strerror(errno));
    #endif
}
