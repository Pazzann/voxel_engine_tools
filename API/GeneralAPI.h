//
// Created by manto on 7/9/2026.
//

#ifndef VOXEL_ENGINE_TOOLS_GENERALAPI_H
#define VOXEL_ENGINE_TOOLS_GENERALAPI_H

#include <cstdint>
#include <unordered_map>
#include <memory>
#include "../Core/World.h"

namespace VoxelEngine{
    namespace API{

#ifdef VOXEL_SMALL_IDS
        using VoxelIdType = uint8_t;  // up to 256 unique voxel definitions
#else
        using VoxelIdType = uint16_t; // up to 65536 unique voxel definitions
#endif

        extern std::unordered_map<int, std::unique_ptr<VoxelEngine::Core::World<VoxelIdType>>> g_worlds;
        extern int g_nextHandle;

    }
}


#endif //VOXEL_ENGINE_TOOLS_GENERALAPI_H
