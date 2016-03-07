cmake_minimum_required(VERSION 3.3)
project(Project2)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -gdwarf-3")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -gdwarf-3")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++11 -fopenmp ")


set(SOURCE_FILES
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
    RBN.h
    resource.h)

add_executable(Project2 ${SOURCE_FILES})