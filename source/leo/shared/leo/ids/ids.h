#pragma once

#include <utils/genericid.h>

namespace puma::leo
{
    const u32 kInvalidPhysicsID = kMaxU32;
    using PhysicsID = u32;
    
    class WorldID;
    class FrameID;
    class FramePartID;
}

DECLARE_GENERIC_ID( puma::leo::WorldID, puma::leo::PhysicsID, kInvalidPhysicsID)
DECLARE_GENERIC_ID( puma::leo::FrameID, puma::leo::PhysicsID, kInvalidPhysicsID )
DECLARE_GENERIC_ID( puma::leo::FramePartID, puma::leo::PhysicsID, kInvalidPhysicsID )