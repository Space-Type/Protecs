/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Unit tests for
** Address struct
*/

#include <gtest/gtest.h>
#include <protecs.hpp>
#include <sstream>


using Protecs::Networking::Address;


TEST(networking_Address, invalidHostname)
{
    EXPECT_THROW(
        Address::construct("Hello, World!", 5123),
        Protecs::NetworkError
    );
}

TEST(networking_Address, validHostname)
{
    auto address = Address::construct("127.0.0.1", 5123);

    EXPECT_EQ(address.host(), "127.0.0.1");
    // Note: testing anything more specific
    // than this is system dependent
}

TEST(networking_Address, validPort)
{
    auto address = Address::construct("127.0.0.1", 5123);

    EXPECT_EQ(address.sin_port, 788);  // 788 is what you get from byte-swapping 5123
    EXPECT_EQ(address.port(), 5123);
}

TEST(networking_Address, validPrint)
{
    auto address = Address::construct("127.0.0.1", 5123);

    std::stringstream stream;
    stream << address;

    EXPECT_EQ(stream.str(), "127.0.0.1:5123");
}

TEST(networking_Address, equalityOperator)
{
    auto address1 = Address::construct("127.0.0.1", 5123);
    auto address2 = Address::construct("127.0.0.1", 5124);
    auto address3 = Address::construct("127.0.0.1", 5123);

    EXPECT_FALSE(address1 == address2);
    EXPECT_FALSE(address2 == address3);
    EXPECT_TRUE(address1  == address3);
    EXPECT_TRUE(address3  == address1);

    EXPECT_TRUE(address1  != address2);
    EXPECT_TRUE(address2  != address3);
    EXPECT_FALSE(address1 != address3);
    EXPECT_FALSE(address3 != address1);
}

TEST(networking_Address, addressHash)
{
    auto address1 = Address::construct("127.0.0.1", 5123);
    auto address2 = Address::construct("127.0.0.1", 5124);
    auto address3 = Address::construct("127.0.0.1", 5123);

    EXPECT_FALSE(std::hash<Address>{}(address1) == std::hash<Address>{}(address2));
    EXPECT_FALSE(std::hash<Address>{}(address2) == std::hash<Address>{}(address3));
    EXPECT_TRUE(std::hash<Address>{}(address1)  == std::hash<Address>{}(address3));
    EXPECT_TRUE(std::hash<Address>{}(address3)  == std::hash<Address>{}(address1));

    EXPECT_TRUE(std::hash<Address>{}(address1)  != std::hash<Address>{}(address2));
    EXPECT_TRUE(std::hash<Address>{}(address2)  != std::hash<Address>{}(address3));
    EXPECT_FALSE(std::hash<Address>{}(address1) != std::hash<Address>{}(address3));
    EXPECT_FALSE(std::hash<Address>{}(address3) != std::hash<Address>{}(address1));
}
