cmake_minimum_required(VERSION 3.12)
project(Milestone_2)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCES
        main.cpp
        server.h)

add_executable(Milestone_2 ${SOURCES})