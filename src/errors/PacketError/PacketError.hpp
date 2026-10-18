/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** PacketError class
*/

#pragma once

#include "../NetworkError/NetworkError.hpp"


namespace Protecs {
    class PacketError : public NetworkError {
        public:
            PacketError(std::string_view msg);
    };
}
