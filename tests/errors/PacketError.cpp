/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Unit tests for
** PacketError class
*/

#include <gtest/gtest.h>
#include <protecs/errors.hpp>


TEST(errors_PacketError, message)
{
    EXPECT_THROW(
        try {
            throw Protecs::PacketError("test");
        } catch (const Protecs::PacketError& err) {
            EXPECT_STREQ(err.what(), "test");
            throw err;
        },
        Protecs::PacketError
    );
}
