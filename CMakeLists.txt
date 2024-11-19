cmake_minimum_required(VERSION 3.29)
project(Projet)

set(CMAKE_CXX_STANDARD 20)

add_executable(Projet main.cpp
        player.h
        player.cpp
        square.h
        tetris.h
        display.h
        display.cpp
        tetris.cpp
        json.hpp
        square.cpp
        board.h
        board.cpp)
