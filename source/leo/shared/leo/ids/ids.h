#pragma once

#include <utils/genericid.h>

namespace puma::leo
{
    const u32 kInvalidPhysicsID = kMaxU32;
    using PhysicsID = u32;
    
    DECLARE_GENERIC_ID( WorldID, PhysicsID, kInvalidPhysicsID)
    DECLARE_GENERIC_ID( FrameID, PhysicsID, kInvalidPhysicsID )
    DECLARE_GENERIC_ID( FramePartID, PhysicsID, kInvalidPhysicsID )
}