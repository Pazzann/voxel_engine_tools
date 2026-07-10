//
// Created by manto on 7/9/2026.
//

#include "WorldAPI.h"
#include "GeneralAPI.h"


int VoxelEngine::API::CreateWorld(VoxelEngine::Core::Coordinates chunkSize) {
    int handle = VoxelEngine::API::g_nextHandle++;
    VoxelEngine::API::g_worlds[handle] = std::make_unique<VoxelEngine::Core::World<VoxelEngine::API::VoxelIdType>>(
            VoxelEngine::Core::Coordinates{chunkSize.x, chunkSize.y, chunkSize.z});
    return handle;
}

void VoxelEngine::API::DestroyWorld(int handle) {
    VoxelEngine::API::g_worlds.erase(handle);
}
