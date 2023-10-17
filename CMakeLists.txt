cmake_minimum_required(VERSION 3.26)
project(kiss)

set(CMAKE_CXX_STANDARD 17)

add_executable(kiss
        main.cpp
        graph.hpp
        graph_infector.hpp
        tests.hpp)
