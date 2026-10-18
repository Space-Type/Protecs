/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Implementation for
** PacketError class
*/

#include "PacketError.hpp"


Protecs::PacketError::PacketError(std::string_view msg)
    : NetworkError(msg)
{

}
