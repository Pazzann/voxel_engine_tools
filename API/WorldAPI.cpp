//
// Created by manto on 7/9/2026.
//

#include "WorldAPI.h"
#include "GeneralAPI.h"
#include "../Core/MeshBuilder.h"
#include <exception>
#include <cstring>
#include <set>



int VoxelEngine::API::CreateWorld(VoxelEngine::Core::Coordinates chunkSize) {
    int handle = VoxelEngine::API::g_nextHandle++;
    VoxelEngine::API::g_worlds[handle] = std::make_unique<VoxelEngine::Core::World<VoxelEngine::API::VoxelIdType>>(
            VoxelEngine::Core::Coordinates{chunkSize.x, chunkSize.y, chunkSize.z});

    VoxelEngine::API::GlobalRegistry.Register({"dirt", {}, {}});

    return handle;
}

void VoxelEngine::API::DestroyWorld(int worldId) {
    VoxelEngine::API::g_worlds.erase(worldId);
}

int VoxelEngine::API::GetVoxel(int worldId, VoxelEngine::Core::GlobalCoords globalCoords) {
    auto it = g_worlds.find(worldId);
    if (it == g_worlds.end()) {
        return -1;
    }
    return it->second->PeekVoxelId(globalCoords);
}

int VoxelEngine::API::SetVoxel(int worldId, VoxelEngine::Core::GlobalCoords globalCoords, int defId) {
    auto it = g_worlds.find(worldId);
    if (it == g_worlds.end()) {
        return -1;
    }
    try {
        VoxelIdType id = static_cast<VoxelIdType>(defId);
        const VoxelEngine::Core::VoxelDefinition& definition = GlobalRegistry.Get(id);
        it->second->SetVoxel(globalCoords, id, definition);
        return 0;
    } catch (const std::exception&) {
        return -2;
    }
}

int VoxelEngine::API::SetVoxels(int worldId, int count, VoxelEngine::Core::GlobalCoords *coords, int defId) {
    auto it = g_worlds.find(worldId);
    if (it == g_worlds.end()) {
        return -1;
    }

    try {
        VoxelIdType id = static_cast<VoxelIdType>(defId);
        const VoxelEngine::Core::VoxelDefinition& definition = GlobalRegistry.Get(id);
        it->second->SetVoxels(coords, definition, count, defId );

        return 0;
    } catch (const std::exception&){
        return -2;
    }

}

int VoxelEngine::API::GetDirtyChunkCount(int worldId) {
    auto it = g_worlds.find(worldId);
    if (it == g_worlds.end()) {
        return -1;
    }
    return static_cast<int>(it->second->GetDirtyChunks().size());
}

int VoxelEngine::API::GetDirtyChunks(int worldId, VoxelEngine::Core::Coordinates *outChunkCoords) {
    auto it = g_worlds.find(worldId);
    if (it == g_worlds.end()) {
        return -1;
    }
    const auto& dirty = it->second->GetDirtyChunks();
    int i = 0;
    for (const auto& coord : dirty) {
        outChunkCoords[i] = coord;
        i++;
    }
    return i;
}

int VoxelEngine::API::BuildChunkMesh(int worldId, VoxelEngine::Core::Coordinates chunkCoords, int *outVertexCount, int *outIndexCount) {
    auto it = g_worlds.find(worldId);
    if (it == g_worlds.end()) {
        return -1;
    }

    auto& world = *(it->second);
    auto& chunk = world.GetChunk(chunkCoords);
    VoxelEngine::Core::Mesh mesh = VoxelEngine::Core::MeshBuilder::CreateMeshFromChunkNaive(chunk, world, chunkCoords);
    world.ClearChunkDirty(chunkCoords);

    *outVertexCount = static_cast<int>(mesh.positions.size() / 3);
    *outIndexCount = static_cast<int>(mesh.indices.size());

    int handle = g_nextMeshHandle++;
    g_pendingMeshes[handle] = std::move(mesh);
    return handle;
}

int VoxelEngine::API::FillAndReleaseChunkMesh(int meshHandle, float *outPositions, float *outNormals, float *outUvs, int *outIndices) {
    auto it = g_pendingMeshes.find(meshHandle);
    if (it == g_pendingMeshes.end()) {
        return -1;
    }

    const auto& mesh = it->second;
    std::memcpy(outPositions, mesh.positions.data(), mesh.positions.size() * sizeof(float));
    std::memcpy(outNormals, mesh.normals.data(), mesh.normals.size() * sizeof(float));
    std::memcpy(outUvs, mesh.uvs.data(), mesh.uvs.size() * sizeof(float));
    std::memcpy(outIndices, mesh.indices.data(), mesh.indices.size() * sizeof(int));

    g_pendingMeshes.erase(it);
    return 0;
}
