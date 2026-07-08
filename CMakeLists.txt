cmake_minimum_required(VERSION 3.29)
project(voxel_engine_tools)

set(CMAKE_CXX_STANDARD 26)

add_library(voxel_engine_tools SHARED Core/Voxel.cpp
        Core/Chunk.h
        Core/Chunk.cpp
        Core/World.cpp
        Core/World.h)
