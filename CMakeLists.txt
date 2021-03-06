cmake_minimum_required(VERSION 3.17)
project(RayTracer)

set(CMAKE_CXX_STANDARD 14)

add_executable(RayTracer
        src/main.cpp
        src/Vector.cpp src/Vector.h
        src/Config.cpp src/Config.h
        src/Triangle.cpp src/Triangle.h
        src/types.h
        src/KdTree.cpp src/KdTree.h
        src/intersect.cpp src/intersect.h
        src/file_io.h src/file_io.cpp
        src/Image.cpp src/Image.h
        src/render.h
        src/scene.h)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -flto")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopt-info")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--whole-archive -lpthread -Wl,--no-whole-archive")