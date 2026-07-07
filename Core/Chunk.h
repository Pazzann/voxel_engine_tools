//
// Created by manto on 7/7/2026.
//

#ifndef VOXEL_ENGINE_TOOLS_CHUNK_H
#define VOXEL_ENGINE_TOOLS_CHUNK_H

#include <memory>
#include "Voxel.h"

namespace VoxelEngine {
    namespace Core {

        template<typename TId = uint16_t>
        class Chunk {
        private:
            int size_z;
            int size_x;
            int size_y;
            std::unique_ptr<Voxel<TId>[]> voxelList;

            const int _coordsToIndex(int x, int y, int z){
                return size_x * size_y * z + size_x *y + x;
            }
        public:
            Chunk(int sx, int sy, int sz)
                    : size_x(sx), size_y(sy), size_z(sz), voxelList(std::make_unique<Voxel<TId>[]>(sx * sy * sz)) {}

            Voxel<TId>& GetVoxel(int x, int y, int z) {
                return voxelList[_coordsToIndex(x,y,z)];
            }
            const Voxel<TId>& GetVoxel(int x, int y, int z) const {
                return voxelList[_coordsToIndex(x, y, z)];
            }
        };

    }
}

#endif //VOXEL_ENGINE_TOOLS_CHUNK_H
