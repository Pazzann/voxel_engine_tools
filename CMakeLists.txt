cmake_minimum_required(VERSION 3.29)
project(voxel_engine_tools)

set(CMAKE_CXX_STANDARD 26)

add_library(voxel_engine_tools SHARED Core/Voxel/Voxel.cpp
        Core/Chunk.h
        Core/Chunk.cpp
        Core/World.cpp
        Core/World.h
        Core/Utils/Cordinates.cpp
        Core/Utils/Cordinates.h
        Core/Voxel/VoxelDefinition.cpp
        Core/Voxel/VoxelDefinition.h
        Core/Voxel/VoxelRegistry.cpp
        Core/Voxel/VoxelRegistry.h
        Core/MeshBuilder.h
        Core/MeshBuilder.cpp)
