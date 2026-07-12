//
// Created by manto on 7/9/2026.
//

#ifndef VOXEL_ENGINE_TOOLS_CORDINATES_H
#define VOXEL_ENGINE_TOOLS_CORDINATES_H

#include <compare>
#include <cstddef>
#include <functional>


namespace VoxelEngine::Core {

    struct ConvertedCoords;

    struct Coordinates {
        int x, y, z;

        auto operator<=>(const Coordinates &) const = default;
    };

    struct GlobalCoords : Coordinates {
        // Floor division/modulo per axis (not truncating like raw / and %),
        // so negative coordinates split into a valid chunk index + in-range local coordinate.
        [[nodiscard]] ConvertedCoords ConvertToLocal(const Coordinates &divisor) const;
    };


    struct ConvertedCoords {
        Coordinates chunkCoords;
        Coordinates inChunkCoords;

        [[nodiscard]] GlobalCoords ConvertToGlobal(const Coordinates &divisor) const;
    };

}


template<>
struct std::hash<VoxelEngine::Core::Coordinates> {
    std::size_t operator()(const VoxelEngine::Core::Coordinates &c) const noexcept {
        std::size_t seed = 0;
        for (int value: {c.x, c.y, c.z}) {
            seed ^= std::hash<int>{}(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

#endif //VOXEL_ENGINE_TOOLS_CORDINATES_H
