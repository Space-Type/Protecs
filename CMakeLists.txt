##
## EPITECH PROJECT, 2026
## Project - Protecs
## File description:
## Main project build
## file
##

cmake_minimum_required(VERSION 3.15)

project(RType-Protocol VERSION 1.0
                       DESCRIPTION "R-Type Network Protocol - R-Type project"
                       HOMEPAGE_URL "https://github.com/Space-Type/Protocol"
                       LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;MinSizeRel;RelWithDebInfo;DebugTests"
                              CACHE STRING "Supported build types" FORCE)

set(CMAKE_CXX_FLAGS_DEBUGTESTS "${CMAKE_CXX_FLAGS_DEBUG}"
                               CACHE STRING "Flags used by the C++ compiler during DebugTests builds.")


if (NOT TARGET wrecks)
    if (CMAKE_BUILD_TYPE STREQUAL "DebugTests")
        set(CMAKE_BUILD_TYPE "Debug")
        set(REVERT_TO_DEBUGTESTS yes)
    endif()

    add_subdirectory(lib/wrecks)

    if (REVERT_TO_DEBUGTESTS STREQUAL yes)
        set(CMAKE_BUILD_TYPE "DebugTests")
    endif()
endif()


set(PROTECS_SOURCES
    src/components/Level/Level.cpp
    src/components/Level/Level.hpp
    src/components/Movement/Movement.cpp
    src/components/Movement/Movement.hpp
    src/components/PathFinding/PathFinding.cpp
    src/components/PathFinding/PathFinding.hpp
    src/components/PlayerInput/PlayerInput.cpp
    src/components/PlayerInput/PlayerInput.hpp
    src/components/PlayerStats/PlayerStats.cpp
    src/components/PlayerStats/PlayerStats.hpp
    src/components/Transform/Transform.cpp
    src/components/Transform/Transform.hpp
    src/components/Velocity/Velocity.cpp
    src/components/Velocity/Velocity.hpp
    src/components/Manager.hpp
    src/errors/Error/Error.cpp
    src/errors/Error/Error.hpp
    src/errors/NetworkError/NetworkError.cpp
    src/errors/NetworkError/NetworkError.hpp
    src/errors/PacketError/PacketError.cpp
    src/errors/PacketError/PacketError.hpp
    src/errors/SerializationError/SerializationError.cpp
    src/errors/SerializationError/SerializationError.hpp
    src/networking/Address/Address.hpp
    src/networking/Address/Address.unix.cpp
    src/networking/Address/Address.win.cpp
    src/networking/NetworkEntity/NetworkEntity.cpp
    src/networking/NetworkEntity/NetworkEntity.hpp
    src/networking/Packet/Packet.cpp
    src/networking/Packet/Packet.hpp
    src/networking/packets/EntityComponentData/EntityComponentData.cpp
    src/networking/packets/EntityComponentData/EntityComponentData.hpp
    src/networking/packets/EntityCreate/EntityCreate.cpp
    src/networking/packets/EntityCreate/EntityCreate.hpp
    src/networking/packets/EntityDelete/EntityDelete.cpp
    src/networking/packets/EntityDelete/EntityDelete.hpp
    src/networking/packets/EntityList/EntityList.cpp
    src/networking/packets/EntityList/EntityList.hpp
    src/networking/packets/EntityRemoveComponent/EntityRemoveComponent.cpp
    src/networking/packets/EntityRemoveComponent/EntityRemoveComponent.hpp
    src/networking/packets/EntitySyncComponents/EntitySyncComponents.cpp
    src/networking/packets/EntitySyncComponents/EntitySyncComponents.hpp
    src/networking/packets/Ping/Ping.cpp
    src/networking/packets/Ping/Ping.hpp
    src/networking/packets/PlayerId/PlayerId.cpp
    src/networking/packets/PlayerId/PlayerId.hpp
    src/networking/packets/PlayerInput/PlayerInput.cpp
    src/networking/packets/PlayerInput/PlayerInput.hpp
    src/networking/packets/PlayerJoin/PlayerJoin.cpp
    src/networking/packets/PlayerJoin/PlayerJoin.hpp
    src/networking/packets/PlayerLeave/PlayerLeave.cpp
    src/networking/packets/PlayerLeave/PlayerLeave.hpp
    src/networking/packets/PacketData.hpp
    src/networking/UDPSocket/UDPSocket.hpp
    src/networking/UDPSocket/UDPSocket.unix.cpp
    src/networking/UDPSocket/UDPSocket.win.cpp
    src/systems/Motion/Motion.cpp
    src/systems/Motion/Motion.hpp
    src/systems/Movement/Movement.cpp
    src/systems/Movement/Movement.hpp
    src/systems/PathFinding/PathFinding.cpp
    src/systems/PathFinding/PathFinding.hpp
    src/systems/Tuple.hpp
    src/utils/Memory.hpp
    src/utils/Vec2D.hpp)

if (WIN32)
    set(EXCLUDED_PLATFORM "unix")
else()
    set(EXCLUDED_PLATFORM "win")
endif()

list(FILTER PROTECS_SOURCES EXCLUDE REGEX "\\.${EXCLUDED_PLATFORM}\\.[ch]pp$")

add_library(protecs STATIC ${PROTECS_SOURCES})
target_include_directories(protecs PUBLIC  include
                                   PRIVATE lib/wrecks/include)
target_link_libraries(protecs wrecks)

if (WIN32)
    target_link_libraries(protecs wsock32 ws2_32)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "DebugTests")
    if (NOT WIN32)
        target_compile_options(protecs PRIVATE --coverage)
        target_link_options(protecs PRIVATE --coverage)
    endif()

    enable_testing()
    add_subdirectory(tests)
endif()
