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

        struct VoxelDefinition{
            std::string tag;
            std::unordered_map<std::string, float> properties;
            std::vector<VoxelState> state;
        };

        template<typename TId = uint16_t>
        struct Voxel{
            TId id;
            std::vector<std::variant<float, int, bool>> state;
        };

        struct Property {
            const char* name;
            float value;
        };

        void register_definitions(const char* tag, Property* properties, int count);

        template<typename TId = uint16_t>
        class VoxelRegistry{
        private:
            std::map<TId, VoxelDefinition> registry;

        public:
            void Register(VoxelDefinition* voxelDefinition);

            VoxelDefinition Get(TId id);
            VoxelDefinition Get(std::string tag);
        };

    }
}
#endif //VOXEL_ENGINE_TOOLS_VOXEL_H
