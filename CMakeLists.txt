##==================================================================================================
##  Roguey
##  Copyright : Joel FALCOU
##  SPDX-License-Identifier: MIT
##==================================================================================================

cmake_minimum_required(VERSION 3.16)
project(ROGUEY CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(Curses REQUIRED)
find_package(Lua REQUIRED)

set(SOURCES
    src/dungeon.cpp
    src/game.cpp
    src/main.cpp
    src/registry.cpp
    src/renderer.cpp
    src/script_engine.cpp
    src/systems.cpp
)

include_directories(include)
add_executable(rogue_game ${SOURCES})
target_link_libraries(rogue_game PRIVATE ${CURSES_LIBRARIES} ${LUA_LIBRARIES} pthread)
target_include_directories(rogue_game PRIVATE ${CURSES_INCLUDE_DIR} ${LUA_INCLUDE_DIR} include)