//
// Created by manto on 7/9/2026.
//

#ifndef VOXEL_ENGINE_TOOLS_WORLDAPI_H
#define VOXEL_ENGINE_TOOLS_WORLDAPI_H

#ifdef _WIN32
#define VOXEL_API extern "C" __declspec(dllexport)
#else
#define VOXEL_API extern "C"
#endif

#include "../Core/Utils/Cordinates.h"
#include "RegistryAPI.h"


namespace VoxelEngine{
    namespace API{

        VOXEL_API int CreateWorld(Core::Coordinates chunkSize);
        VOXEL_API void DestroyWorld(int worldId);
        // Returns the voxel id (>= 0), or -1 if worldId doesn't refer to a live world.
        VOXEL_API int GetVoxel(int worldId, Core::GlobalCoords globalCoords);

        // Returns 0 on success, -1 for an invalid worldId, -2 if defId was never registered.
        VOXEL_API int SetVoxel(int worldId, Core::GlobalCoords globalCoords, int defId);


        // Number of chunks whose mesh is currently stale, or -1 if worldId is invalid. Call this to
        // size the array you pass to GetDirtyChunks.
        VOXEL_API int GetDirtyChunkCount(int worldId);

        // Fills outChunkCoords (caller-allocated, sized per GetDirtyChunkCount) with the dirty chunk
        // coordinates. Returns how many were written, or -1 if worldId is invalid. Reading the list
        // does NOT clear it — a chunk stops being dirty only when BuildChunkMesh rebuilds it.
        VOXEL_API int GetDirtyChunks(int worldId, Core::Coordinates* outChunkCoords);

        // Builds the mesh for the given chunk (coords come from GetDirtyChunks) and caches it under
        // its own handle; also clears that chunk's dirty flag. Any number of meshes can be pending at
        // once. Writes vertex count (positions/normals need 3 floats each, uvs need 2) and index
        // count to the out-params. Returns the handle for FillAndReleaseChunkMesh, or -1 if worldId
        // doesn't refer to a live world.
        VOXEL_API int BuildChunkMesh(int worldId, Core::Coordinates chunkCoords, int* outVertexCount, int* outIndexCount);

        // Copies the cached mesh for meshHandle into caller-allocated buffers (sized per the counts
        // BuildChunkMesh reported) and erases that entry. Returns 0 on success, -1 if meshHandle
        // doesn't refer to a pending mesh (unknown, or already collected).
        VOXEL_API int FillAndReleaseChunkMesh(int meshHandle, float* outPositions, float* outNormals, float* outUvs, int* outIndices);
    }
}


#endif //VOXEL_ENGINE_TOOLS_WORLDAPI_H

