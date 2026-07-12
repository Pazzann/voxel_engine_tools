//
// Created by manto on 7/8/2026.
//

#ifndef VOXEL_ENGINE_TOOLS_WORLD_H
#define VOXEL_ENGINE_TOOLS_WORLD_H

#include <cstdint>
#include <memory>
#include <unordered_set>
#include <vector>
#include "Chunk.h"
#include "Voxel/Voxel.h"
#include "Voxel/VoxelDefinition.h"
#include <climits>


namespace VoxelEngine::Core {

    template<typename TId = uint16_t>
    class World {
    private:
        const Coordinates chunk_size;

        std::unordered_map<Coordinates, std::unique_ptr<Chunk<TId>>> chunks;

        // Chunk coords whose mesh is stale and needs rebuilding. A chunk is added here when it
        // (or, for edits on a chunk boundary, a face-adjacent neighbor) is written to, and
        // removed when its mesh is rebuilt.
        std::unordered_set<Coordinates> dirtyChunks;

        // Marks the edited chunk dirty, plus any face-adjacent neighbor when the edited voxel
        // sits on that face — meshing reads across chunk borders, so a boundary edit invalidates
        // the neighbor's mesh too. Only the 6 face-neighbors matter (meshing never consults
        // diagonal chunks).
        void markDirtyWithNeighbors(Coordinates chunkCoords, Coordinates inChunkCoords) {
            dirtyChunks.insert(chunkCoords);
            if (inChunkCoords.x == 0) dirtyChunks.insert({chunkCoords.x - 1, chunkCoords.y, chunkCoords.z});
            if (inChunkCoords.x == chunk_size.x - 1)
                dirtyChunks.insert({chunkCoords.x + 1, chunkCoords.y, chunkCoords.z});
            if (inChunkCoords.y == 0) dirtyChunks.insert({chunkCoords.x, chunkCoords.y - 1, chunkCoords.z});
            if (inChunkCoords.y == chunk_size.y - 1)
                dirtyChunks.insert({chunkCoords.x, chunkCoords.y + 1, chunkCoords.z});
            if (inChunkCoords.z == 0) dirtyChunks.insert({chunkCoords.x, chunkCoords.y, chunkCoords.z - 1});
            if (inChunkCoords.z == chunk_size.z - 1)
                dirtyChunks.insert({chunkCoords.x, chunkCoords.y, chunkCoords.z + 1});
        }

    public:
        World(Coordinates chunk_size) : chunk_size(chunk_size) {}

        Voxel<TId> &GetVoxelFromWorldCoord(GlobalCoords globalCoords) {
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

        Chunk<TId> &GetChunk(Coordinates chunkCoords) {
            auto [it, inserted] = chunks.try_emplace(chunkCoords, nullptr);
            if (inserted) {
                it->second = std::make_unique<Chunk<TId>>(chunk_size);
            }
            return *(it->second);
        }

        // The caller (API layer) resolves `definition` from the registry and passes it in —
        // World stays a pure spatial store with no knowledge of the registry.
        Voxel<TId> &SetVoxel(GlobalCoords globalCoords, TId id, const VoxelDefinition &definition) {
            ConvertedCoords convertedCoords = globalCoords.ConvertToLocal(chunk_size);

            Voxel<TId> &voxel = GetChunk(convertedCoords.chunkCoords).SetVoxel(convertedCoords.inChunkCoords, id,
                                                                               definition);
            markDirtyWithNeighbors(convertedCoords.chunkCoords, convertedCoords.inChunkCoords);
            return voxel;
        }

        void SetVoxels(GlobalCoords *coordsArrays, const VoxelDefinition &def, int count, TId defId) {
            Coordinates lastChunkCoord = {INT_MIN, INT_MIN, INT_MIN};
            Chunk<TId> *current = nullptr;
            for (int i = 0; i < count; i++) {
                ConvertedCoords convertedCoords = coordsArrays[i].ConvertToLocal(chunk_size);
                if (convertedCoords.chunkCoords != lastChunkCoord) {
                    current = &GetChunk(convertedCoords.chunkCoords);
                    markDirtyWithNeighbors(convertedCoords.chunkCoords, convertedCoords.inChunkCoords);
                    lastChunkCoord = convertedCoords.chunkCoords;
                }

                current->SetVoxel(convertedCoords.inChunkCoords, defId, def);

            }
        }

        const std::unordered_set<Coordinates> &GetDirtyChunks() const {
            return dirtyChunks;
        }

        void ClearChunkDirty(Coordinates chunkCoords) {
            dirtyChunks.erase(chunkCoords);
        }

    };


}


#endif //VOXEL_ENGINE_TOOLS_WORLD_H
