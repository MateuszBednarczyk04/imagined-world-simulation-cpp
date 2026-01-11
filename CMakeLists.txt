cmake_minimum_required(VERSION 3.21)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

# Create the executable target
add_executable(untitled main.cpp
        impl/organisms/animals/Animal.cpp)

# Add the 'abstract' directory to the include path for our target
target_include_directories(untitled PUBLIC abstract)

# Use GLOB_RECURSE to find all .cpp files in the 'impl' directory and its subdirectories
file(GLOB_RECURSE IMPL_SOURCES "impl/*.cpp")

# Add the found source files to our executable target
target_sources(untitled PRIVATE ${IMPL_SOURCES})
