//
// Created by manto on 7/8/2026.
//

#ifndef VOXEL_ENGINE_TOOLS_WORLD_H
#define VOXEL_ENGINE_TOOLS_WORLD_H

#include <cstdint>
#include <tuple>
#include <map>
#include <memory>
#include "Chunk.h"
#include "Voxel.h"

namespace VoxelEngine {
    namespace Core {

        template<typename TId = uint16_t>
        class World{
        private:
            const int chunk_size_x;
            const int chunk_size_y;
            const int chunk_size_z;

            std::map<std::tuple<int,int,int>, std::unique_ptr<Chunk<TId>>> chunks;

            const std::tuple<int,int,int> _voxelWorldCoordsToChunkCoords(int x, int y, int z) const;
        public:

            World(int chunk_size_x, int chunk_size_y, int chunk_size_z): chunk_size_x(chunk_size_x), chunk_size_y(chunk_size_y), chunk_size_z(chunk_size_z){

            }

            Voxel<TId>& GetVoxelFromWorldCoord(int x, int y, int z);
            const Voxel<TId>& GetVoxelFromWorldCoord(int x, int y, int z) const;

            Chunk<TId>& GetChunk(int x, int y, int z);
            const Chunk<TId>& GetChunk(int x, int y, int z) const;
        };


    }
}


#endif //VOXEL_ENGINE_TOOLS_WORLD_H
