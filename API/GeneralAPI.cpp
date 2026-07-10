//
// Created by manto on 7/9/2026.
//
#include "GeneralAPI.h"



std::unordered_map<int, std::unique_ptr<VoxelEngine::Core::World<VoxelEngine::API::VoxelIdType>>> VoxelEngine::API::g_worlds;
int VoxelEngine::API::g_nextHandle = 1;

std::unordered_map<int, VoxelEngine::Core::Mesh> VoxelEngine::API::g_pendingMeshes;
int VoxelEngine::API::g_nextMeshHandle = 1;

