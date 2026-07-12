//
// Created by manto on 7/12/2026.
//

#ifndef VOXEL_ENGINE_TOOLS_RAYCAST_H
#define VOXEL_ENGINE_TOOLS_RAYCAST_H

#include <cmath>
#include "../Core/Utils/Cordinates.h"
#include "../Core/World.h"


namespace VoxelEngine::Utils {
    struct RaycastHit {
        bool hit;
        Core::Coordinates voxel;   // the solid voxel that was hit
        Core::Coordinates normal;  // face normal (which way the hit face points) — for placing adjacent
    };


    //raycast from any point of the world
    template<typename TId>
    RaycastHit Raycast(const Core::World<TId> &world, float ox, float oy, float oz,
                       float dx, float dy, float dz, float maxDist) {

        int x = (int) std::floor(ox), y = (int) std::floor(oy), z = (int) std::floor(oz);

        int stepX = dx > 0 ? 1 : -1, stepY = dy > 0 ? 1 : -1, stepZ = dz > 0 ? 1 : -1;

        // distance (in t) to cross one full voxel on each axis
        float tDeltaX = dx != 0 ? std::abs(1.0f / dx) : INFINITY;
        float tDeltaY = dy != 0 ? std::abs(1.0f / dy) : INFINITY;
        float tDeltaZ = dz != 0 ? std::abs(1.0f / dz) : INFINITY;

        // distance (in t) to the FIRST voxel boundary on each axis
        float tMaxX = dx != 0 ? ((stepX > 0 ? (x + 1 - ox) : (ox - x)) / std::abs(dx)) : INFINITY;
        float tMaxY = dy != 0 ? ((stepY > 0 ? (y + 1 - oy) : (oy - y)) / std::abs(dy)) : INFINITY;
        float tMaxZ = dz != 0 ? ((stepZ > 0 ? (z + 1 - oz) : (oz - z)) / std::abs(dz)) : INFINITY;

        Core::Coordinates normal = {0, 0, 0};
        float t = 0.0f;
        while (t <= maxDist) {
            if (world.PeekVoxelId({{x, y, z}}) != 0) {
                return {true, {x, y, z}, normal};
            }
            // advance into the next voxel across the nearest boundary
            if (tMaxX < tMaxY && tMaxX < tMaxZ) {
                x += stepX;
                t = tMaxX;
                tMaxX += tDeltaX;
                normal = {-stepX, 0, 0};
            } else if (tMaxY < tMaxZ) {
                y += stepY;
                t = tMaxY;
                tMaxY += tDeltaY;
                normal = {0, -stepY, 0};
            } else {
                z += stepZ;
                t = tMaxZ;
                tMaxZ += tDeltaZ;
                normal = {0, 0, -stepZ};
            }
        }
        return {false, {0, 0, 0}, {0, 0, 0}};
    }

}


#endif //VOXEL_ENGINE_TOOLS_RAYCAST_H
