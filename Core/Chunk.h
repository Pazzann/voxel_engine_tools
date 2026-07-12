//
// Created by manto on 7/7/2026.
//

#ifndef VOXEL_ENGINE_TOOLS_CHUNK_H
#define VOXEL_ENGINE_TOOLS_CHUNK_H

#include <memory>
#include "Voxel/Voxel.h"
#include "Utils/Cordinates.h"
#include "Voxel/VoxelDefinition.h"


namespace VoxelEngine::Core {

    template<typename TId = uint16_t>
    class Chunk {
    private:
        const Coordinates size;
        std::unique_ptr<Voxel<TId>[]> voxelList;

        const int _coordsToIndex(Coordinates coords) const {
            return size.x * size.y * coords.z + size.x * coords.y + coords.x;
        }

    public:
        Chunk(Coordinates size)
                : size(size), voxelList(std::make_unique<Voxel<TId>[]>(size.x * size.y * size.z)) {}

        Coordinates GetSize() const {
            return size;
        }

        Voxel<TId> &GetVoxel(Coordinates coords) {
            return voxelList[_coordsToIndex(coords)];
        }

        const Voxel<TId> &GetVoxel(Coordinates coords) const {
            return voxelList[_coordsToIndex(coords)];
        }

        Voxel<TId> &SetVoxel(Coordinates localCoords, TId id, const VoxelDefinition &definition) {
            Voxel<TId> &voxel = voxelList[_coordsToIndex(localCoords)];
            voxel.id = id;
            voxel.state.clear();
            voxel.state.reserve(definition.state.size());
            for (const auto &voxelState: definition.state) {
                voxel.state.push_back(voxelState.value);
            }
            return voxel;
        }
    };

}


#endif //VOXEL_ENGINE_TOOLS_CHUNK_H
