/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Header file for
** SerializationError class
*/

#pragma once

#include "../Error/Error.hpp"


namespace Protecs {
    class SerializationError : public Error {
        public:
            SerializationError(std::string_view msg);
    };
}
