##
## EPITECH PROJECT, 2026
## Project - Protecs
## File description:
## Unit test build
## file
##

cmake_minimum_required(VERSION 3.15)

include(FetchContent)

FetchContent_Declare(googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE)

FetchContent_MakeAvailable(googletest)

set(TEST_SOURCES
    components/Level.cpp
    components/PathFinding.cpp
    components/PlayerStats.cpp
    components/Transform.cpp
    components/Velocity.cpp
    errors/Error.cpp
    errors/NetworkError.cpp
    errors/PacketError.cpp
    networking/packets/PlayerId.cpp
    networking/packets/PlayerInput.cpp
    networking/packets/PlayerJoin.cpp
    networking/packets/PlayerLeave.cpp
    networking/Address.cpp
    networking/NetworkEntity.cpp
    networking/UDPSocket.cpp
    networking/UDPSocket.unix.cpp
    networking/UDPSocket.win.cpp
    systems/Motion.cpp
    systems/PathFinding.cpp
    utils/Memory.cpp)

if (WIN32)
    set(EXCLUDED_PLATFORM "unix")
else()
    set(EXCLUDED_PLATFORM "win")
endif()

list(FILTER TEST_SOURCES EXCLUDE REGEX "\\.${EXCLUDED_PLATFORM}\\.[ch]pp$")

add_executable(protecs_tests ${TEST_SOURCES})

target_link_libraries(protecs_tests PRIVATE protecs
                                    PRIVATE GTest::gtest_main)

set_target_properties(protecs_tests PROPERTIES MAP_IMPORTED_CONFIG_DEBUGTESTS Debug)
target_compile_options(protecs_tests PRIVATE --coverage)
target_link_options(protecs_tests PRIVATE --coverage)

include(GoogleTest)
gtest_discover_tests(protecs_tests)
