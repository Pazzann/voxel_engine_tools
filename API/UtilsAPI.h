//
// Created by manto on 7/12/2026.
//

#ifndef VOXEL_ENGINE_TOOLS_UTILSAPI_H
#define VOXEL_ENGINE_TOOLS_UTILSAPI_H

#include "../Core/Voxel/VoxelRegistry.h"
#include "GeneralAPI.h"
#include "WorldAPI.h"
#include "../Utils/Raycast.h"

namespace VoxelEngine::API {


    // Gets raycast from the world and the coords. -1 means world not found
    // 0 means no hit, 1 means hit 
    VOXEL_API int Raycast(int worldId, float ox, float oy, float oz,
                                        float dx, float dy, float dz, float maxDist, Core::Coordinates *target, Core::Coordinates *normal);

}


#endif //VOXEL_ENGINE_TOOLS_UTILSAPI_H
