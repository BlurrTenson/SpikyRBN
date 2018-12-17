cmake_minimum_required(VERSION 3.6)
project(Spike)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")
include_directories(.)

add_executable(Spike
        Bond.cpp
        Bond.h
        InteractionList.cpp
        InteractionList.h
        main.cpp
        Node.cpp
        Node.h
        Particle.cpp
        Particle.h
        RBN.cpp
        RBN.h)
