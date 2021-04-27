#pragma once
#include <utils/geometry/shapes/shape.h>

namespace puma::physics
{
    struct BodyInfo
    {
        Shape shape;
        CollisionIndex collisionIndex = kDefaultCollisionID;
        float density = 0.0f;
        float friction = 0.2f;
        float restitution = 0.0f;
        UserCollisionData userData = nullptr;
    };
}