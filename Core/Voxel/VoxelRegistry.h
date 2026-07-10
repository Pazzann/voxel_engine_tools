//
// Created by manto on 7/9/2026.
//

#ifndef VOXEL_ENGINE_TOOLS_VOXELREGISTRY_H
#define VOXEL_ENGINE_TOOLS_VOXELREGISTRY_H

#include <cstdint>
#include <stdexcept>
#include "VoxelDefinition.h"

namespace VoxelEngine {
    namespace Core {



        template<typename TId = uint16_t>
        class VoxelRegistry{
        private:
            std::unordered_map<TId, VoxelDefinition> registry;

            //id 0 means air
            TId next_id = 0;
        public:

            VoxelRegistry(){
                Register({"air", {}, {}});
            }

            TId Register(const VoxelDefinition& voxelDefinition){
                TId id = next_id;
                registry.emplace(next_id, voxelDefinition);
                next_id++;
                return id;
            };

            VoxelDefinition& Get(TId id){
                return registry.at(id);
            };
            [[nodiscard]] const VoxelDefinition& Get(std::string tag) const{
                for (const auto& pair : registry) {
                    if (pair.second.tag == tag){
                        return pair.second;
                    }
                }
                throw std::out_of_range("Index is out of the map or vector bounds");
            };
        };

    }
}
#endif //VOXEL_ENGINE_TOOLS_VOXELREGISTRY_H
