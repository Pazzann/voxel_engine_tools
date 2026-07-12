//
// Created by manto on 7/9/2026.
//

#ifndef VOXEL_ENGINE_TOOLS_VOXELDEFINITION_H
#define VOXEL_ENGINE_TOOLS_VOXELDEFINITION_H

#include <string>
#include <unordered_map>
#include <vector>
#include "Voxel.h"


namespace VoxelEngine::Core {
    struct VoxelDefinition {
        std::string tag;
        std::unordered_map<std::string, float> properties;
        std::vector<VoxelState> state;
    };
}


#endif //VOXEL_ENGINE_TOOLS_VOXELDEFINITION_H
