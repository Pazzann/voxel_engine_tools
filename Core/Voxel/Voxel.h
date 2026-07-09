#ifndef VOXEL_ENGINE_TOOLS_VOXEL_H
#define VOXEL_ENGINE_TOOLS_VOXEL_H

#include <string>
#include <map>
#include <cstdint>
#include <unordered_map>
#include <variant>
#include <vector>

namespace VoxelEngine {
    namespace Core{

        struct VoxelState{
            std::variant<float, int, bool> value;
            std::string name;
        };


        template<typename TId = uint16_t>
        struct Voxel{
            TId id;
            std::vector<std::variant<float, int, bool>> state;
        };

        struct VoxelProperty {
            const char* name;
            float value;
        };


    }
}
#endif //VOXEL_ENGINE_TOOLS_VOXEL_H
