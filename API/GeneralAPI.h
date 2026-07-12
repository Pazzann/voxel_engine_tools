//
// Created by manto on 7/9/2026.
//

#ifndef VOXEL_ENGINE_TOOLS_GENERALAPI_H
#define VOXEL_ENGINE_TOOLS_GENERALAPI_H

#include <cstdint>
#include <unordered_map>
#include <memory>
#include "../Core/World.h"
#include "../Utils/MeshBuilder.h"


namespace VoxelEngine::API {

#ifdef VOXEL_SMALL_IDS
    using VoxelIdType = uint8_t;  // up to 256 unique voxel definitions
#else
    using VoxelIdType = uint16_t; // up to 65536 unique voxel definitions
#endif

    extern std::unordered_map<int, std::unique_ptr<VoxelEngine::Core::World<VoxelIdType>>> g_worlds;
    extern int g_nextHandle;

    // Any number of meshes can be built and pending at once, each under its own handle — e.g. an
    // edit that dirties several neighboring chunks can build all of them before any get collected.
    extern std::unordered_map<int, VoxelEngine::Utils::Mesh> g_pendingMeshes;
    extern int g_nextMeshHandle;

}


#endif //VOXEL_ENGINE_TOOLS_GENERALAPI_H
