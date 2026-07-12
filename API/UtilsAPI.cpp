//
// Created by manto on 7/12/2026.
//

#include "UtilsAPI.h"


int VoxelEngine::API::Raycast(int worldId, float ox, float oy, float oz, float dx, float dy, float dz, float maxDist,
                              VoxelEngine::Core::Coordinates *voxel, VoxelEngine::Core::Coordinates *normal) {
    auto it = g_worlds.find(worldId);
    if (it == g_worlds.end()) {
        return -1;
    }

    auto hit = VoxelEngine::Utils::Raycast(*(it->second), ox, oy, oz, dx, dy, dz, maxDist);

    *voxel = hit.voxel;
    *normal = hit.normal;

    return hit.hit;
}