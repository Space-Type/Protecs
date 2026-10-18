/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Unit tests for
** Error class
*/

#include <gtest/gtest.h>
#include <protecs/errors.hpp>


TEST(errors_Error, message)
{
    EXPECT_THROW(
        try {
            throw Protecs::Error("test");
        } catch (const Protecs::Error& err) {
            EXPECT_STREQ(err.what(), "test");
            throw err;
        },
        Protecs::Error
    );
}
