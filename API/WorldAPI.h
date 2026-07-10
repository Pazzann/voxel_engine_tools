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


namespace VoxelEngine{
    namespace API{

        VOXEL_API int CreateWorld(VoxelEngine::Core::Coordinates chunkSize);
        VOXEL_API void DestroyWorld(int handle);

    }
}


#endif //VOXEL_ENGINE_TOOLS_WORLDAPI_H

