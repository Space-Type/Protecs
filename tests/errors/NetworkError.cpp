/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Unit tests for
** NetworkError class
*/

#include <gtest/gtest.h>
#include <protecs.hpp>


TEST(errors_NetworkError, message)
{
    std::string_view message = "bob";

    EXPECT_THROW(
        try {
            throw Protecs::NetworkError(message);
        } catch (const Protecs::NetworkError& error) {
            EXPECT_EQ(message, error.what());
            throw error;
        },
        Protecs::Error
    );
}

TEST(errors_NetworkError, isErrorBase)
{
    EXPECT_THROW(throw Protecs::NetworkError("test"), Protecs::Error);
}
