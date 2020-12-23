#include <precompiledphysics.h>

#include <internal/ids/idhelper.h>
#include <internal/ids/ids.h>

namespace puma::physics
{

    const WorldID IdHelper::buildWorldID( PhysicsID _worldIndex )
    {
        PhysicsID id = 0;
        serializeWorldID( id, _worldIndex, SerializeMode::WriteID );
        return WorldID( id );
    }

    const FrameID IdHelper::buildDynamicFrameID( PhysicsID _worldIndex, PhysicsID _frameIndex )
    {
        PhysicsID id = 0;
        FrameType frameType = FrameType::Dynamic;
        serializeFrameID( id, _worldIndex, frameType, _frameIndex, SerializeMode::WriteID );
        return FrameID( id );
    }

    const FrameID IdHelper::buildStaticFrameID( PhysicsID _worldIndex, PhysicsID _frameIndex )
    {
        PhysicsID id = 0;
        FrameType frameType = FrameType::Static;
        serializeFrameID( id, _worldIndex, frameType, _frameIndex, SerializeMode::WriteID );
        return FrameID( id );
    }

    const FrameID IdHelper::buildKinematicFrameID( PhysicsID _worldIndex, PhysicsID _frameIndex )
    {
        PhysicsID id = 0;
        FrameType frameType = FrameType::Kinematic;
        serializeFrameID( id, _worldIndex, frameType, _frameIndex, SerializeMode::WriteID );
        return FrameID( id );
    }

    const FramePartID IdHelper::buildFrameBodyID( PhysicsID _frameId, PhysicsID _framePartIndex )
    {
        PhysicsID id = 0;
        PhysicsID worldIndex = 0;
        FrameType frameType = FrameType::Invalid;
        PhysicsID frameIndex = 0;
        serializeFrameID( _frameId, worldIndex, frameType, frameIndex, SerializeMode::ReadID );
        FramePartType framePartType = FramePartType::Body;
        serializeFramePartID( id, worldIndex, frameType, frameIndex, framePartType, _framePartIndex, SerializeMode::WriteID );

        return FramePartID( id );
    }

    const FramePartID IdHelper::buildFrameTriggerID( PhysicsID _frameId, PhysicsID _framePartIndex )
    {
        PhysicsID id = 0;
        PhysicsID worldIndex = 0;
        FrameType frameType = FrameType::Invalid;
        PhysicsID frameIndex = 0;
        serializeFrameID( _frameId, worldIndex, frameType, frameIndex, SerializeMode::ReadID );
        FramePartType framePartType = FramePartType::Trigger;
        serializeFramePartID( id, worldIndex, frameType, frameIndex, framePartType, _framePartIndex, SerializeMode::WriteID );

        return FramePartID( id );
    }

    void IdHelper::readWorldID( WorldID _worldId, PhysicsID& _worldIndex )
    {
        PhysicsID id = _worldId.value();
        serializeWorldID( id, _worldIndex, SerializeMode::ReadID );
        assert( _worldIndex < kMaxWorldCount );
    }

    void IdHelper::readFrameID( FrameID _id, PhysicsID& _worldIndex, FrameType& _frameType, PhysicsID& _frameIndex )
    {
        PhysicsID id = _id.value();
        serializeFrameID( id, _worldIndex, _frameType, _frameIndex, SerializeMode::ReadID );

        assert( _worldIndex < kMaxWorldCount );
        assert( _frameType < FrameType::Count );
        assert( _frameIndex < kMaxFrameCount );
    }

    void IdHelper::readFramePartID( FramePartID _id, PhysicsID& _worldIndex, FrameType& _frameType, PhysicsID& _frameIndex, FramePartType& _framePartType, PhysicsID& _framePartIndex )
    {
        PhysicsID id = _id.value();
        serializeFramePartID( id, _worldIndex, _frameType, _frameIndex, _framePartType, _framePartIndex, SerializeMode::ReadID );

        assert( _worldIndex < kMaxWorldCount );
        assert( _frameType < FrameType::Count );
        assert( _frameIndex < kMaxFrameCount );
        assert( _framePartType < FramePartType::Count );
        assert( _framePartIndex < kMaxFramePartCount );
    }

    void IdHelper::serializeWorldID( PhysicsID& _worldId, PhysicsID& _worldIndex, SerializeMode _mode )
    {
        u32 cursor = 0;

        switch ( _mode )
        {
        case SerializeMode::ReadID:
            readWorldIndex( _worldId, _worldIndex, cursor );
            break;
        case SerializeMode::WriteID:
            appendWorldIndex( _worldId, _worldIndex, cursor );
            break;
        default:
            break;
        }
    }

    void IdHelper::serializeFrameID( PhysicsID& _frameId, PhysicsID& _worldIndex, FrameType& _frameType, PhysicsID& _frameIndex, SerializeMode _mode )
    {
        u32 cursor = 0;

        switch ( _mode )
        {
        case SerializeMode::ReadID:
            readFrameIndex( _frameId, _frameIndex, cursor );
            readFrameType( _frameId, _frameType, cursor );
            readWorldIndex( _frameId, _worldIndex, cursor );
            break;
        case SerializeMode::WriteID:
            appendFrameIndex( _frameId, _frameIndex, cursor );
            appendFrameType( _frameId, _frameType, cursor );
            appendWorldIndex( _frameId, _worldIndex, cursor );
            break;
        default:
            break;
        }
    }

    void IdHelper::serializeFramePartID( PhysicsID& _frameId, PhysicsID& _worldIndex, FrameType& _frameType, PhysicsID& _frameIndex, FramePartType& _framePartType, PhysicsID& _framePartIndex, SerializeMode _mode )
    {
        u32 cursor = 0;

        switch ( _mode )
        {
        case SerializeMode::ReadID:
            readFramePartIndex( _frameId, _framePartIndex, cursor );
            readFramePartType( _frameId, _framePartType, cursor );
            readFrameIndex( _frameId, _frameIndex, cursor );
            readFrameType( _frameId, _frameType, cursor );
            readWorldIndex( _frameId, _worldIndex, cursor );
            break;
        case SerializeMode::WriteID:
            appendFramePartIndex( _frameId, _framePartIndex, cursor );
            appendFramePartType( _frameId, _framePartType, cursor );
            appendFrameIndex( _frameId, _frameIndex, cursor );
            appendFrameType( _frameId, _frameType, cursor );
            appendWorldIndex( _frameId, _worldIndex, cursor );
            break;
        default:
            break;
        }
    }

    //-----------------------------------------------------
    void IdHelper::readWorldIndex( PhysicsID _id, PhysicsID& _worldIndex, u32& _cursor )
    {
        PhysicsID worldIndexMask = (PhysicsID)~0x0 >> ((8 * sizeof( PhysicsID )) - kWorldIdBitCount);
        _id = _id >> _cursor;
        _worldIndex = _id & worldIndexMask;
        _cursor += kWorldIdBitCount;

        assert( _worldIndex < kMaxWorldCount );
    }

    void IdHelper::readFrameType( PhysicsID _id, FrameType& _frameType, u32& _cursor )
    {
        PhysicsID frameTypeMask = (PhysicsID)~0x0 >> ((8 * sizeof( PhysicsID )) - kFrameTypeBitCount);
        _id = _id >> _cursor;
        _frameType = static_cast<FrameType>(_id & frameTypeMask);
        _cursor += kFrameTypeBitCount;

        assert( _frameType < FrameType::Count );
    }

    void IdHelper::readFrameIndex( PhysicsID _id, PhysicsID& _frameIndex, u32& _cursor )
    {
        PhysicsID frameIndexMask = (PhysicsID)~0x0 >> ((8 * sizeof( PhysicsID )) - kFrameIdBitCount);
        _id = _id >> _cursor;
        _frameIndex = _id & frameIndexMask;
        _cursor += kFrameIdBitCount;

        assert( _frameIndex < kMaxFrameCount );
    }

    void IdHelper::readFramePartIndex( PhysicsID _id, PhysicsID& _framePartIndex, u32& _cursor )
    {
        PhysicsID framePartIndexMask = (PhysicsID)~0x0 >> ((8 * sizeof( PhysicsID )) - kFramePartIdBitCount);
        _id = _id >> _cursor;
        _framePartIndex = _id & framePartIndexMask;
        _cursor += kFramePartIdBitCount;

        assert( _framePartIndex < kMaxFramePartCount );
    }

    void IdHelper::readFramePartType( PhysicsID _id, FramePartType& _framePartType, u32& _cursor )
    {
        PhysicsID framePartIndexMask = (PhysicsID)~0x0 >> ((8 * sizeof( PhysicsID )) - kFramePartTypeBitCount);
        _id = _id >> _cursor;
        _framePartType = static_cast<FramePartType>(_id & framePartIndexMask);
        _cursor += kFramePartTypeBitCount;

        assert( _framePartType < FramePartType::Count );
    }

    //---------------------------------------------------
    void IdHelper::appendWorldIndex( PhysicsID& _id, PhysicsID _worldIndex, u32& _cursor )
    {
        assert( _worldIndex < kMaxWorldCount );

        _worldIndex = _worldIndex << _cursor;
        _id += _worldIndex;
        _cursor += kWorldIdBitCount;
    }

    void IdHelper::appendFrameType( PhysicsID& _id, FrameType _frameType, u32& _cursor )
    {
        assert( _frameType < FrameType::Count );

        PhysicsID frameType = (PhysicsID)_frameType << _cursor;
        _id += frameType;
        _cursor += kFrameTypeBitCount;
    }

    void IdHelper::appendFrameIndex( PhysicsID& _id, PhysicsID _frameIndex, u32& _cursor )
    {
        assert( _frameIndex < kMaxFrameCount );

        _frameIndex = _frameIndex << _cursor;
        _id += _frameIndex;
        _cursor += kFrameIdBitCount;
    }

    void IdHelper::appendFramePartIndex( PhysicsID& _id, PhysicsID _framePartIndex, u32& _cursor )
    {
        assert( _framePartIndex < kMaxFramePartCount );

        _framePartIndex = _framePartIndex << _cursor;
        _id += _framePartIndex;
        _cursor += kFramePartIdBitCount;
    }

    void IdHelper::appendFramePartType( PhysicsID& _id, FramePartType _framePartType, u32& _cursor )
    {
        assert( _framePartType < FramePartType::Count);
                
        PhysicsID framePartType = (PhysicsID)_framePartType << _cursor;
        _id += framePartType;
        _cursor += kFramePartTypeBitCount;
    }

}