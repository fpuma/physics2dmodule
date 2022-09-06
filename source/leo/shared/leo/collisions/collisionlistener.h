#pragma once

#include <utils/containers/containedvector.h>
#include <utils/geometry/vec2.h>

namespace puma::leo
{

    using ContactPoint = Vec2;
    
    class ICollisionListener
    {
    public:

        virtual ~ICollisionListener() {}

        virtual void collisionStarted( FramePartID _framePartA, FramePartID _framePartB, ContactPoint _contactPoint ) = 0;
        virtual void collisionStopped( FramePartID _framePartA, FramePartID _framePartB ) = 0;
    };
}
