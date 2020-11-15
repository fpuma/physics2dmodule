#pragma once
#include <internal/ids/ids.h>

namespace puma::physics
{
    class IdHelper
    {
    public:

        static const WorldID buildWorldID( PhysicsID _worldIndex );

        static const FrameID buildDynamicFrameID( PhysicsID _worldIndex, PhysicsID _frameIndex );
        static const FrameID buildStaticFrameID( PhysicsID _worldIndex, PhysicsID _frameIndex );
        static const FrameID buildKinematicFrameID( PhysicsID _worldIndex, PhysicsID _frameIndex );
        
        static const FramePartID buildFrameBodyID( PhysicsID _frameId, PhysicsID _framePartIndex );
        static const FramePartID buildFrameTriggerID( PhysicsID _frameId, PhysicsID _framePartIndex );

        static void readFrameID( FrameID _id, PhysicsID& _worldIndex, FrameType& _frameType, PhysicsID& _frameIndex );

        static void readFramePartID( FramePartID _id, PhysicsID& _worldIndex, FrameType& _frameType, PhysicsID& _frameIndex, FramePartType& _framePartType, PhysicsID& _framePartIndex );

    private:

        enum class SerializeMode
        {
            ReadID,
            WriteID,
        };

        static void serializeWorldID( PhysicsID& _worldId, PhysicsID& _worldIndex, SerializeMode _mode );

        static void serializeFrameID( PhysicsID& _frameId, PhysicsID& _worldIndex, FrameType& _frameType, PhysicsID& _frameIndex, SerializeMode _mode );

        static void serializeFramePartID( PhysicsID& _frameId, PhysicsID& _worldIndex, FrameType& _frameType, PhysicsID& _frameIndex, FramePartType& _framePartType, PhysicsID& _framePartIndex, SerializeMode _mode );

        //-----------------------------------------------------
        static void readWorldIndex( PhysicsID _id, PhysicsID& _worldIndex, u32& _cursor );

        static void readFrameType( PhysicsID _id, FrameType& _frameType, u32& _cursor );

        static void readFrameIndex( PhysicsID _id, PhysicsID& _frameIndex, u32& _cursor );

        static void readFramePartIndex( PhysicsID _id, PhysicsID& _framePartIndex, u32& _cursor );

        static void readFramePartType( PhysicsID _id, FramePartType& _framePartType, u32& _cursor );

        //---------------------------------------------------
        static void appendWorldIndex( PhysicsID& _id, PhysicsID _worldIndex, u32& _cursor );

        static void appendFrameType( PhysicsID& _id, FrameType _frameType, u32& _cursor );

        static void appendFrameIndex( PhysicsID& _id, PhysicsID _frameIndex, u32& _cursor );

        static void appendFramePartIndex( PhysicsID& _id, PhysicsID _framePartIndex, u32& _cursor );
        
        static void appendFramePartType( PhysicsID& _id, FramePartType _framePartType, u32& _cursor );
    };
}