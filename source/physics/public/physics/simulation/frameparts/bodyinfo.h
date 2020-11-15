#pragma once
#include <physics/geometry/shapes.h>

namespace puma::physics
{
    struct BodyInfo
    {
        Shape shape;
        ShapeType shapeType;
        CollisionIndex collisionIndex = kDefaultCollisionID;
        float density = 0.0f;
        float friction = 0.2f;
        float restitution = 0.0f;
        UserCollisionData userData = nullptr;
    };
}