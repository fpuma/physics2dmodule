#pragma once
#include <utils/geometry/shapes/shape.h>

namespace puma::physics
{
    struct TriggerInfo
    {
        Shape shape;
        float density = 0.0f;
        CollisionIndex collisionIndex = kDefaultCollisionID;
        UserCollisionData userData = nullptr;
    };
}