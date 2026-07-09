//
// Created by manto on 7/8/2026.
//

#ifndef VOXEL_ENGINE_TOOLS_WORLD_H
#define VOXEL_ENGINE_TOOLS_WORLD_H

#include <cstdint>
#include <memory>
#include "Chunk.h"
#include "Voxel/Voxel.h"
#include "Voxel/VoxelRegistry.h"

namespace VoxelEngine {
    namespace Core {

        template<typename TId = uint16_t>
        class World{
        private:
            const Coordinates chunk_size;
            VoxelRegistry<TId> registry;


            std::unordered_map<Coordinates, std::unique_ptr<Chunk<TId>>> chunks;

        public:
            World(Coordinates chunk_size): chunk_size(chunk_size){}

            Voxel<TId>& GetVoxelFromWorldCoord(GlobalCoords globalCoords){
                ConvertedCoords convertedCoords = globalCoords.ConvertToLocal(chunk_size);
                return GetChunk(convertedCoords.chunkCoords).GetVoxel(convertedCoords.inChunkCoords);
            };


            TId PeekVoxelId(GlobalCoords globalCoords) const {
                ConvertedCoords convertedCoords = globalCoords.ConvertToLocal(chunk_size);
                auto it = chunks.find(convertedCoords.chunkCoords);
                if (it == chunks.end()) {
                    return 0;
                }
                return it->second->GetVoxel(convertedCoords.inChunkCoords).id;
            }

            Chunk<TId>& GetChunk(Coordinates chunkCoords){
                auto [it, inserted] = chunks.try_emplace(chunkCoords, nullptr);
                if (inserted) {
                    it->second = std::make_unique<Chunk<TId>>(chunk_size);
                }
                return *(it->second);
            }

            Voxel<TId>& SetVoxel(GlobalCoords globalCoords, TId id){
                ConvertedCoords convertedCoords = globalCoords.ConvertToLocal(chunk_size);
                return GetChunk(convertedCoords.chunkCoords).SetVoxel(convertedCoords.inChunkCoords, id, registry.Get(id));
            }

            TId Register(const VoxelDefinition& voxelDefinition){
                return registry.Register(voxelDefinition);
            };

        };


    }
}


#endif //VOXEL_ENGINE_TOOLS_WORLD_H
