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
        Utils/MeshBuilder.h
        Utils/MeshBuilder.cpp
        API/WorldAPI.cpp
        API/WorldAPI.h
        API/GeneralAPI.cpp
        API/GeneralAPI.h
        API/RegistryAPI.cpp
        API/RegistryAPI.h)

# Where the C# wrapper project expects to find the native DLL. Adjust if your
# checkout of the C# repo lives somewhere else.
set(CSHARP_WRAPPER_LIB_DIR
        "C:/Users/manto/OneDrive/Documents/GitHub/voxel_engine_tools_csharp_wrapper/VoxelEngineTools/VoxelEngineTools/lib")

# Statically link the MinGW/GCC runtime so the DLL has no external libgcc/libstdc++
# dependencies — it must load standalone inside any host (Godot, Unity, Python), which
# won't have MinGW's bin on PATH.
add_compile_options(-static)
add_link_options(-static -static-libgcc -static-libstdc++)

# Big variant: 2-byte voxel id, up to 65536 unique voxel definitions.
add_library(voxel_engine_tools_big SHARED ${VOXEL_ENGINE_SOURCES}
        Utils/Raycast.cpp
        Utils/Raycast.h
        API/UtilsAPI.cpp
        API/UtilsAPI.h
)
add_custom_command(TARGET voxel_engine_tools_big POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CSHARP_WRAPPER_LIB_DIR}"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "$<TARGET_FILE:voxel_engine_tools_big>"
                "${CSHARP_WRAPPER_LIB_DIR}/voxel_engine_tools.dll")

# Small variant: 1-byte voxel id, up to 256 unique voxel definitions.
add_library(voxel_engine_tools_small SHARED ${VOXEL_ENGINE_SOURCES})
target_compile_definitions(voxel_engine_tools_small PRIVATE VOXEL_SMALL_IDS)
add_custom_command(TARGET voxel_engine_tools_small POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CSHARP_WRAPPER_LIB_DIR}"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "$<TARGET_FILE:voxel_engine_tools_small>"
                "${CSHARP_WRAPPER_LIB_DIR}/voxel_engine_tools.dll")
