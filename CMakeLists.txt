cmake_minimum_required(VERSION 3.12)
project(Milestone_2)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCES
        main.cpp
        server/server.h
        server/serialServer.h
        server/clientHandler.h
        server/testClientHandler.cpp server/testClientHandler.h
        algorithms/solver.h
        algorithms/search_algorithms.h
        algorithms/searchable.h
        algorithms/state.h
        )

add_executable(Milestone_2 ${SOURCES})