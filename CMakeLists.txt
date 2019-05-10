cmake_minimum_required(VERSION 3.13)
project(APT_Assignment_2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(APT_Assignment_2
        GameEngine.cpp
        GameEngine.h
        LinkedList.cpp
        LinkedList.h
        Node.cpp
        Node.h
        Player.cpp
        Player.h
        Position.cpp
        Position.h
        qwirkle.cpp
        Tile.cpp
        Tile.h
        TileCodes.h)
