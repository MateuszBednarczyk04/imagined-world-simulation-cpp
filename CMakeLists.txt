cmake_minimum_required(VERSION 3.31)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled main.cpp
        abstract/World.h
        impl/World.cpp
        abstract/Organism.h
        abstract/Animal.h
        abstract/Plant.h
        impl/Plant.cpp
        abstract/Antelope.h
        impl/Antelope.cpp
        abstract/SosnowskyHogweed.h
        impl/SosnowskyHogweed.cpp
        abstract/CyberSheep.h
        impl/CyberSheep.cpp
        abstract/Grass.h
        impl/Grass.cpp
        abstract/Wolf.h
        impl/Wolf.cpp
        abstract/Sheep.h
        impl/Sheep.cpp
        abstract/Fox.h
        impl/Fox.cpp
        abstract/Turtle.h
        impl/Turtle.cpp
        abstract/Dandelion.h
        impl/Dandelion.cpp
        abstract/Guarana.h
        impl/Guarana.cpp
        abstract/Belladonna.h
        impl/Belladonna.cpp
        abstract/Human.h
        impl/Human.cpp
)
