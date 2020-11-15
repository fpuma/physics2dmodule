#pragma once

#include <utils/genericid.h>

namespace puma::physics
{
    const u32 kInvalidPhysicsID = kMaxU32;
    using PhysicsID = u32;
    
    class WorldID : public GenericID<PhysicsID, kInvalidPhysicsID> 
    {
    public:
        WorldID() {}
        WorldID( PhysicsID _id )
            : GenericID( _id )
        {}
    };
    
    class FrameID : public GenericID<PhysicsID, kInvalidPhysicsID> 
    {
    public:
        FrameID() {}
        FrameID( PhysicsID _id )
            : GenericID( _id )
        {}
    };
    
    class FramePartID : public GenericID<PhysicsID, kInvalidPhysicsID> 
    {
    public:
        FramePartID() {}
        FramePartID( PhysicsID _id )
            : GenericID( _id )
        {}
    };
    
}