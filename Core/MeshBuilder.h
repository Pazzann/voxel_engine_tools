//
// Created by manto on 7/9/2026.
//

#ifndef VOXEL_ENGINE_TOOLS_MESHBUILDER_H
#define VOXEL_ENGINE_TOOLS_MESHBUILDER_H

#include <vector>
#include "Chunk.h"
#include "World.h"
#include "Utils/Cordinates.h"

namespace VoxelEngine {
    namespace Core {

        struct Mesh{
            std::vector<float> positions;
            std::vector<float> normals;
            std::vector<float> uvs;
            std::vector<int> indices;
        };

        class MeshBuilder{
        private:
            struct FaceDirection {
                Coordinates neighborOffset;
                float normal[3];
                float corners[4][3]; // 4 corners of the face, wound counter-clockwise as seen from outside
            };

            // One entry per cube face. Winding order verified against its normal via the right-hand rule
            // (cross of consecutive edges points the same way as `normal`), so backface culling won't hide these.
            static constexpr FaceDirection kDirections[6] = {
                { {1,0,0},  {1,0,0},  {{1,0,0},{1,1,0},{1,1,1},{1,0,1}} }, // +X
                { {-1,0,0}, {-1,0,0}, {{0,0,1},{0,1,1},{0,1,0},{0,0,0}} }, // -X
                { {0,1,0},  {0,1,0},  {{0,1,0},{0,1,1},{1,1,1},{1,1,0}} }, // +Y
                { {0,-1,0}, {0,-1,0}, {{0,0,1},{0,0,0},{1,0,0},{1,0,1}} }, // -Y
                { {0,0,1},  {0,0,1},  {{1,0,1},{1,1,1},{0,1,1},{0,0,1}} }, // +Z
                { {0,0,-1}, {0,0,-1}, {{0,0,0},{0,1,0},{1,1,0},{1,0,0}} }, // -Z
            };

            static bool InBounds(Coordinates coords, Coordinates size) {
                return coords.x >= 0 && coords.x < size.x
                    && coords.y >= 0 && coords.y < size.y
                    && coords.z >= 0 && coords.z < size.z;
            }

        public:
            template<typename TId = uint16_t>
            static Mesh CreateMeshFromChunkNaive(const Chunk<TId>& chunk, const World<TId>& world, Coordinates chunkCoords){
                Mesh mesh;
                Coordinates size = chunk.GetSize();

                for (int z = 0; z < size.z; z++){
                    for (int y = 0; y < size.y; y++){
                        for (int x = 0; x < size.x; x++){
                            Coordinates voxelCoords{x, y, z};
                            const Voxel<TId>& voxel = chunk.GetVoxel(voxelCoords);
                            if (voxel.id == 0){
                                continue; // air, nothing to mesh here
                            }

                            for (const auto& dir : kDirections){
                                Coordinates neighborCoords{
                                    x + dir.neighborOffset.x,
                                    y + dir.neighborOffset.y,
                                    z + dir.neighborOffset.z
                                };

                                bool exposed;
                                if (InBounds(neighborCoords, size)){
                                    exposed = chunk.GetVoxel(neighborCoords).id == 0;
                                } else {
                                    // Neighbor falls in another chunk — ask World without creating it
                                    // if it doesn't exist (PeekVoxelId reports air in that case).
                                    GlobalCoords voxelGlobalCoords = ConvertedCoords{chunkCoords, voxelCoords}.ConvertToGlobal(size);
                                    GlobalCoords neighborGlobalCoords{{
                                        voxelGlobalCoords.x + dir.neighborOffset.x,
                                        voxelGlobalCoords.y + dir.neighborOffset.y,
                                        voxelGlobalCoords.z + dir.neighborOffset.z
                                    }};
                                    exposed = world.PeekVoxelId(neighborGlobalCoords) == 0;
                                }
                                if (!exposed){
                                    continue;
                                }

                                int baseIndex = static_cast<int>(mesh.positions.size() / 3);

                                for (int c = 0; c < 4; c++){
                                    mesh.positions.push_back(static_cast<float>(x) + dir.corners[c][0]);
                                    mesh.positions.push_back(static_cast<float>(y) + dir.corners[c][1]);
                                    mesh.positions.push_back(static_cast<float>(z) + dir.corners[c][2]);

                                    mesh.normals.push_back(dir.normal[0]);
                                    mesh.normals.push_back(dir.normal[1]);
                                    mesh.normals.push_back(dir.normal[2]);
                                }

                                // Placeholder UVs: same fixed unit-square mapping for every face for now,
                                // regardless of voxel type or which face this is.
                                mesh.uvs.push_back(0.0f); mesh.uvs.push_back(0.0f);
                                mesh.uvs.push_back(1.0f); mesh.uvs.push_back(0.0f);
                                mesh.uvs.push_back(1.0f); mesh.uvs.push_back(1.0f);
                                mesh.uvs.push_back(0.0f); mesh.uvs.push_back(1.0f);

                                mesh.indices.push_back(baseIndex + 0);
                                mesh.indices.push_back(baseIndex + 1);
                                mesh.indices.push_back(baseIndex + 2);
                                mesh.indices.push_back(baseIndex + 0);
                                mesh.indices.push_back(baseIndex + 2);
                                mesh.indices.push_back(baseIndex + 3);
                            }
                        }
                    }
                }

                return mesh;
            }
        };
    }
}
#endif //VOXEL_ENGINE_TOOLS_MESHBUILDER_H
