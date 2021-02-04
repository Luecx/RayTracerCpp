cmake_minimum_required(VERSION 3.17)
project(RayTracer)

set(CMAKE_CXX_STANDARD 14)

add_executable(RayTracer
        src/main.cpp
        src/Vector.h
        src/Vector.cpp
        src/Config.h
        src/Config.cpp)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -flto")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--whole-archive -lpthread -Wl,--no-whole-archive")