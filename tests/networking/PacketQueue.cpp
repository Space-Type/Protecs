/*
** EPITECH PROJECT, 2026
** Project - Protecs
** File description:
** Unit tests for
** PacketQueue class
*/

#include <gtest/gtest.h>
#include <protecs.hpp>


using Protecs::Networking::PacketQueue;
namespace Packets = Protecs::Networking::Packets;


static const auto SENDER_ADDR = Protecs::Networking::Address::construct("127.0.0.1", 5432);


TEST(networking_PacketQueue, simplePush)
{
    PacketQueue queue;

    EXPECT_NO_THROW(queue.push(SENDER_ADDR, Packets::Ping{}));
}

TEST(networking_PacketQueue, emptyPop)
{
    PacketQueue queue;

    EXPECT_NO_THROW(EXPECT_FALSE(queue.pop().has_value()));
}

TEST(networking_PacketQueue, emptyTickPop)
{
    PacketQueue queue;

    EXPECT_NO_THROW(EXPECT_FALSE(queue.pop(10).has_value()));
}

TEST(networking_PacketQueue, isEmpty)
{
    PacketQueue queue;

    EXPECT_TRUE(queue.empty());
    ASSERT_NO_THROW(queue.push(SENDER_ADDR, Packets::Ping{}));
    EXPECT_FALSE(queue.empty());
}

TEST(networking_PacketQueue, sortedInsert)
{
    PacketQueue queue;

    EXPECT_NO_THROW(queue.push(SENDER_ADDR, Packets::EntityCreate{ 7, 123 }));
    EXPECT_NO_THROW(queue.push(SENDER_ADDR, Packets::PlayerInput{ 6, 2 }));
    EXPECT_NO_THROW(queue.push(SENDER_ADDR, Packets::Ping{}));
    EXPECT_NO_THROW(queue.push(SENDER_ADDR, Packets::EntityCreate{ 5, 321 }));
    EXPECT_NO_THROW(queue.push(SENDER_ADDR, Packets::PlayerInput{ 9, 1 }));
    EXPECT_NO_THROW(queue.push(SENDER_ADDR, Packets::PlayerInput{ 9, 2 }));
    EXPECT_NO_THROW(queue.push(SENDER_ADDR, Packets::Ping{}));
    EXPECT_NO_THROW(queue.push(SENDER_ADDR, Packets::PlayerInput{ 6, 4 }));
    EXPECT_NO_THROW(queue.push(SENDER_ADDR, Packets::EntityCreate{ 7, 321 }));
    EXPECT_NO_THROW(queue.push(SENDER_ADDR, Packets::EntityCreate{ 7, 321 }));
    EXPECT_NO_THROW(queue.push(SENDER_ADDR, Packets::PlayerInput{ 10, 5 }));
    EXPECT_NO_THROW(queue.push(SENDER_ADDR, Packets::EntityCreate{ 10, 92 }));
    EXPECT_NO_THROW(queue.push(SENDER_ADDR, Packets::EntityCreate{ 11, 14 }));
    EXPECT_NO_THROW(queue.push(SENDER_ADDR, Packets::PlayerInput{ 11, 3 }));
}

TEST(networking_PacketQueue, sorting)
{
    PacketQueue queue;

    ASSERT_NO_THROW(queue.push(SENDER_ADDR, Packets::EntityCreate{ 7, 123 }));
    ASSERT_NO_THROW(queue.push(SENDER_ADDR, Packets::PlayerInput{ 6, 2 }));
    ASSERT_NO_THROW(queue.push(SENDER_ADDR, Packets::EntityCreate{ 5, 321 }));
    ASSERT_NO_THROW(queue.push(SENDER_ADDR, Packets::PlayerInput{ 6, 1 }));
    ASSERT_NO_THROW(queue.push(SENDER_ADDR, Packets::Ping{}));
    ASSERT_FALSE(queue.empty());

    auto element = queue.pop();
    ASSERT_TRUE(element.has_value());
    EXPECT_TRUE(std::holds_alternative<Packets::Ping>(element->second.deserialize()));

    element = queue.pop();
    ASSERT_TRUE(element.has_value());
    ASSERT_TRUE(std::holds_alternative<Packets::EntityCreate>(element->second.deserialize()));
    EXPECT_EQ(std::get<Packets::EntityCreate>(element->second.deserialize()).id, 321);

    element = queue.pop(5);
    EXPECT_FALSE(element.has_value());

    element = queue.pop(6);
    ASSERT_TRUE(element.has_value());
    ASSERT_TRUE(std::holds_alternative<Packets::PlayerInput>(element->second.deserialize()));
    EXPECT_EQ(std::get<Packets::PlayerInput>(element->second.deserialize()).sequence, 1);

    element = queue.pop(6);
    ASSERT_TRUE(element.has_value());
    ASSERT_TRUE(std::holds_alternative<Packets::PlayerInput>(element->second.deserialize()));
    EXPECT_EQ(std::get<Packets::PlayerInput>(element->second.deserialize()).sequence, 2);

    element = queue.pop(6);
    EXPECT_FALSE(element.has_value());

    element = queue.pop();
    ASSERT_TRUE(element.has_value());
    ASSERT_TRUE(std::holds_alternative<Packets::EntityCreate>(element->second.deserialize()));
    EXPECT_EQ(std::get<Packets::EntityCreate>(element->second.deserialize()).id, 123);
}

TEST(networking_PacketQueue, invalidPacketTickPop)
{
    PacketQueue queue;

    Protecs::Networking::Packet invalidPacket;
    invalidPacket.raw[0] = 255;
    invalidPacket.filled = 1;

    ASSERT_NO_THROW(queue.push(SENDER_ADDR, std::move(invalidPacket)));
    EXPECT_NO_THROW(EXPECT_TRUE(queue.pop(5).has_value()));
}

TEST(networking_PacketQueue, invalidPacketOrdering)
{
    PacketQueue queue;
    Protecs::Networking::Packet invalidPacket;
    invalidPacket.raw[0] = 255;
    invalidPacket.filled = 1;

    EXPECT_NO_THROW(queue.push(SENDER_ADDR, std::move(invalidPacket)));
    EXPECT_NO_THROW(queue.push(SENDER_ADDR, std::move(invalidPacket)));
    EXPECT_NO_THROW(queue.push(SENDER_ADDR, std::move(invalidPacket)));
    EXPECT_NO_THROW(queue.push(SENDER_ADDR, Packets::Ping{}));
    EXPECT_NO_THROW(queue.push(SENDER_ADDR, std::move(invalidPacket)));

    EXPECT_FALSE(queue.empty());
    EXPECT_NO_THROW(EXPECT_TRUE(queue.pop(10).has_value()));
}

TEST(networking_PacketQueue, queueSwap)
{
    PacketQueue queue1;
    PacketQueue queue2;

    ASSERT_NO_THROW(queue1.push(SENDER_ADDR, Packets::EntityCreate{ 3 }));

    EXPECT_FALSE(queue1.empty());
    EXPECT_TRUE(queue2.empty());

    EXPECT_NO_THROW(queue2 = std::move(queue1));

    EXPECT_TRUE(queue1.empty());
    EXPECT_FALSE(queue2.empty());

    std::swap(queue1, queue2);

    EXPECT_FALSE(queue1.empty());
    EXPECT_TRUE(queue2.empty());
}
