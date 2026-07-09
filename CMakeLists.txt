cmake_minimum_required(VERSION 3.29)
project(voxel_engine_tools)

set(CMAKE_CXX_STANDARD 26)

set(VOXEL_ENGINE_SOURCES
        Core/Voxel/Voxel.cpp
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
        Core/MeshBuilder.cpp
        API/WorldAPI.cpp
        API/WorldAPI.h
        API/GeneralAPI.cpp
        API/GeneralAPI.h)

# Big variant: 2-byte voxel id, up to 65536 unique voxel definitions.
add_library(voxel_engine_tools_big SHARED ${VOXEL_ENGINE_SOURCES})

# Small variant: 1-byte voxel id, up to 256 unique voxel definitions.
add_library(voxel_engine_tools_small SHARED ${VOXEL_ENGINE_SOURCES})
target_compile_definitions(voxel_engine_tools_small PRIVATE VOXEL_SMALL_IDS)
