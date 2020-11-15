#pragma once
#include <physics/geometry/vec2.h>
#include <physics/geometry/shapes.h>

namespace puma::physics
{
    struct FrameInfo
    {
        Vec2 position;
        float angle = 0.0f;
        Vec2 linearVelocity;
        float angularVelocity = 0.0f;
        float linearDamping = 0.0f;
        float angularDamping = 0.0f;
        bool preventRotation = false;
        bool initiallyActive = true;
        float gravityScale = 1.0f;
    };    
}