#pragma once

#include "Vector3.h"
#include "Matrix3x4.h"

struct Model {
    void* handle;
    char name[260];
    int	loadFlags;
    int	serverCount;
    int	type;
    int	flags;
    Vector3 mins, maxs;
};

struct ModelRenderInfo {
    Vector3 origin;
    Vector3 angles;
    char pad[4];
    void* renderable;
    const Model* model;
    const Matrix3x4* modelToWorld;
    const Matrix3x4* lightingOffset;
    const Vector3* lightingOrigin;
    int flags;
    int entityIndex;
};
