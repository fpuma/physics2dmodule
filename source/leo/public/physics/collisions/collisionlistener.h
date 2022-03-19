#pragma once

namespace puma::leo
{
    class ICollisionListener
    {
    public:

        virtual ~ICollisionListener() {}

        virtual void collisionStarted( FramePartID _framePartPtrA, FramePartID _framePartPtrB ) = 0;
        virtual void collisionStopped( FramePartID _framePartPtrA, FramePartID _framePartPtrB ) = 0;
    };
}
