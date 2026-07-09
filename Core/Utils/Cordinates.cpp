//
// Created by manto on 7/9/2026.
//

#include "Cordinates.h"

VoxelEngine::Core::ConvertedCoords VoxelEngine::Core::GlobalCoords::ConvertToLocal(const Coordinates& divisor) const {
    ConvertedCoords result;
    auto floorDivMod = [](int value, int size, int& q, int& r) {
        q = value / size;
        r = value % size;
        if (r < 0) {
            q -= 1;
            r += size;
        }
    };
    floorDivMod(x, divisor.x, result.chunkCoords.x, result.inChunkCoords.x);
    floorDivMod(y, divisor.y, result.chunkCoords.y, result.inChunkCoords.y);
    floorDivMod(z, divisor.z, result.chunkCoords.z, result.inChunkCoords.z);
    return result;
}

VoxelEngine::Core::GlobalCoords
VoxelEngine::Core::ConvertedCoords::ConvertToGlobal(const VoxelEngine::Core::Coordinates &divisor) const {
    return {{
        chunkCoords.x * divisor.x + inChunkCoords.x,
        chunkCoords.y * divisor.y + inChunkCoords.y,
        chunkCoords.z * divisor.z + inChunkCoords.z
    }};
}
