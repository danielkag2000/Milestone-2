cmake_minimum_required(VERSION 3.12)
project(Milestone_2)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCES
        main.cpp
        server/server.h
        server/serialServer.h server/serialServer.cpp
        server/clientHandler.h server/clientHandler.cpp
        server/testClientHandler.cpp server/testClientHandler.h
        solve_problem/solver.h
#        algorithms/search_algorithms.h
        solve_problem/searchable.h
        solve_problem/state.h
        solve_problem/search_algorithms.h solve_problem/search_algorithms.cpp
#        algorithms/search_algorithms.cpp
        algorithms/fileCacheManager.h
        algorithms/cacheManager.h
#        algorithms/state_for_test.h
        test.h
        solve_problem/algo_imp.h
        server/sockets/socket_exceptions.h
        server/sockets/sockets.cpp server/sockets/sockets.h)

add_executable(Milestone_2 ${SOURCES} server/fdbuf.cpp server/fdbuf.h server/sockets/sockets.h server/sockets/socket_exceptions.h server/sockets/sockets.cpp server/parallelServer.cpp server/parallelServer.h server/threads/ThreadPool.cpp server/threads/ThreadPool.h)