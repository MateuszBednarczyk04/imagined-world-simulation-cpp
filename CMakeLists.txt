cmake_minimum_required(VERSION 4.0)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled main.cpp
        abstract/World.h
        impl/World.cpp
        abstract/Organism.h
        impl/Organism.cpp
)
