# Minimum CMake version required
cmake_minimum_required(VERSION 3.0)

# Project name and version
project(MyServerProject VERSION 1.0)

# Set C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)

# Add the executable target
add_executable(MyServerProgram main.cpp)