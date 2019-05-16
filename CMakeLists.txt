cmake_minimum_required(VERSION 3.13)
project(APT_Assignment_2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(APT_Assignment_2
        tests/saveTemplate.save
        tests/test1.input
        tests/test1.output
        tests/test1.save
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
