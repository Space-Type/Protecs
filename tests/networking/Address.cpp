/*
** EPITECH PROJECT, 2026
** Project - Wrecks
** File description:
** Unit tests for
** Address struct
*/

#include <gtest/gtest.h>
#include <protecs.hpp>
#include <sstream>


TEST(networking_Address, invalidHostname)
{
    EXPECT_THROW(
        Protecs::Networking::Address::construct("Hello, World!", 5123),
        Protecs::NetworkError
    );
}

TEST(networking_Address, validHostname)
{
    auto address = Protecs::Networking::Address::construct("127.0.0.1", 5123);

    EXPECT_EQ(address.host(), "127.0.0.1");
    // Note: testing anything more specific
    // than this is system dependent
}

TEST(networking_Address, validPort)
{
    auto address = Protecs::Networking::Address::construct("127.0.0.1", 5123);

    EXPECT_EQ(address.sin_port, 788);  // 788 is what you get from byte-swapping 5123
    EXPECT_EQ(address.port(), 5123);
}

TEST(networking_Address, validPrint)
{
    auto address = Protecs::Networking::Address::construct("127.0.0.1", 5123);

    std::stringstream stream;
    stream << address;

    EXPECT_EQ(stream.str(), "127.0.0.1:5123");
}
