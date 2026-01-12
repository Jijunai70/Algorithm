cmake_minimum_required(VERSION 3.22)
project(Algorithm)

set(CMAKE_CXX_STANDARD 20)

add_executable(algorithm
        main.cpp
        src/AdaBoosting.cpp)

target_include_directories(algorithm PRIVATE
        include)