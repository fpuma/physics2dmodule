#include <precompiledphysics.h>

#include <internal/physics.h>

#include <internal/ids/ids.h>
#include <internal/ids/idhelper.h>
#include <internal/simulation/world/world.h>

namespace puma::physics
{
    std::unique_ptr<IPhysics> IPhysics::create()
    {
        return std::make_unique<Physics>();
    }

    void Physics::update( float _deltaTime )
    {
        for(World& world : m_worlds)
        {
            world.update( _deltaTime );
        }
    }

    WorldID Physics::addWorld( Vec2 _gravity )
    {
        assert( m_worlds.size() < kMaxWorldCount );
        WorldID newWorldId{ (PhysicsID)m_worlds.size() };
        m_worlds.emplace_back( _gravity, newWorldId );
        return newWorldId;
    }

    World* Physics::getWorld( WorldID _worldId )
    {
        assert( _worldId.value() < kMaxWorldCount );
        assert( _worldId.value() < m_worlds.size() );
        return &m_worlds[_worldId.value()];
    }

    const World* Physics::getWorld( WorldID _worldId ) const
    {
        assert( _worldId.value() < kMaxWorldCount );
        assert( _worldId.value() < m_worlds.size() );
        return &m_worlds[_worldId.value()];
    }

    namespace
    {
        const IFrame* internalGetFrame( FrameID _frameId, const std::vector<World>& _worlds, FrameType* _outFrameType = nullptr )
        {
            PhysicsID worldIndex = kMaxU32;
            FrameType frameType = FrameType::Invalid;
            PhysicsID frameIndex = kMaxU32;

            IdHelper::readFrameID( _frameId, worldIndex, frameType, frameIndex );

            const IFrame* framePtr = nullptr;

            switch ( frameType )
            {
            case FrameType::Dynamic:    framePtr = _worlds[worldIndex].getDynamicFrame( frameIndex ); break;
            case FrameType::Static:     framePtr = _worlds[worldIndex].getStaticFrame( frameIndex ); break;
            case FrameType::Kinematic:  framePtr = _worlds[worldIndex].getKinematicFrame( frameIndex ); break;
            default: assert( false ); break;
            }

            assert( nullptr != framePtr );

            if ( nullptr != _outFrameType )
            {
                *_outFrameType = frameType;
            }

            return framePtr;
        }

        const IFramePart* internalGetFramePart( FramePartID _framePartId, const std::vector<World>& _worlds, FramePartType* _outFramePartType = nullptr )
        {
            PhysicsID worldIndex = kMaxU32;
            FrameType frameType = FrameType::Invalid;
            PhysicsID frameIndex = kMaxU32;
            FramePartType framePartType = FramePartType::Invalid;
            PhysicsID framePartIndex = kMaxU32;

            IdHelper::readFramePartID( _framePartId, worldIndex, frameType, frameIndex, framePartType, framePartIndex );

            const IFramePart* framePartPtr = nullptr;

            switch ( framePartType )
            {
            case FramePartType::Body:
                switch ( frameType )
                {
                case FrameType::Dynamic:    framePartPtr = _worlds[worldIndex].getDynamicFrame( frameIndex )->getFrameBody( framePartIndex ); break;
                case FrameType::Static:     framePartPtr = _worlds[worldIndex].getStaticFrame( frameIndex )->getFrameBody( framePartIndex ); break;
                case FrameType::Kinematic:  framePartPtr = _worlds[worldIndex].getKinematicFrame( frameIndex )->getFrameBody( framePartIndex ); break;
                default: assert( false ); break;
                }
                break;
            case FramePartType::Trigger:
                switch ( frameType )
                {
                case FrameType::Dynamic:    framePartPtr = _worlds[worldIndex].getDynamicFrame( frameIndex )->getFrameTrigger( framePartIndex ); break;
                case FrameType::Static:     framePartPtr = _worlds[worldIndex].getStaticFrame( frameIndex )->getFrameTrigger( framePartIndex ); break;
                case FrameType::Kinematic:  framePartPtr = _worlds[worldIndex].getKinematicFrame( frameIndex )->getFrameTrigger( framePartIndex ); break;
                default: assert( false ); break;
                }
                break;
            default: assert( false ); break;
            }

            assert( nullptr != framePartPtr );

            if ( nullptr != _outFramePartType )
            {
                *_outFramePartType = framePartType;
            }

            return framePartPtr;
        }
    }

    IFrame* Physics::getFrame( FrameID _frameId )
    {
        return const_cast<IFrame*>(internalGetFrame( _frameId, m_worlds ));
    }

    const IFrame* Physics::getFrame( FrameID _frameId ) const
    {
        return internalGetFrame( _frameId, m_worlds );
    }

    DynamicFrame* Physics::getDynamicFrame( FrameID _frameId ) 
    {
        FrameType frameType = FrameType::Invalid;
        const DynamicFrame* result = static_cast<const DynamicFrame*>(internalGetFrame( _frameId, m_worlds, &frameType ));
        assert( frameType == FrameType::Dynamic );
        return const_cast<DynamicFrame*>(result);
    }

    const DynamicFrame* Physics::getDynamicFrame( FrameID _frameId ) const
    {
        FrameType frameType = FrameType::Invalid;
        const DynamicFrame* result = static_cast<const DynamicFrame*>(internalGetFrame( _frameId, m_worlds, &frameType ));
        assert( frameType == FrameType::Dynamic );
        return result;
    }

    StaticFrame* Physics::getStaticFrame( FrameID _frameId ) 
    {
        FrameType frameType = FrameType::Invalid;
        const StaticFrame* result = static_cast<const StaticFrame*>(internalGetFrame( _frameId, m_worlds, &frameType ));
        assert( frameType == FrameType::Static );
        return const_cast<StaticFrame*>(result);
    }

    const StaticFrame* Physics::getStaticFrame( FrameID _frameId ) const
    {
        FrameType frameType = FrameType::Invalid;
        const StaticFrame* result = static_cast<const StaticFrame*>(internalGetFrame( _frameId, m_worlds, &frameType ));
        assert( frameType == FrameType::Static );
        return result;
    }

    KinematicFrame* Physics::getKinematicFrame( FrameID _frameId ) 
    {
        FrameType frameType = FrameType::Invalid;
        const KinematicFrame* result = static_cast<const KinematicFrame*>(internalGetFrame( _frameId, m_worlds, &frameType ));
        assert( frameType == FrameType::Kinematic );
        return const_cast<KinematicFrame*>(result);
    }

    const KinematicFrame* Physics::getKinematicFrame( FrameID _frameId ) const
    {
        FrameType frameType = FrameType::Invalid;
        const KinematicFrame* result = static_cast<const KinematicFrame*>(internalGetFrame( _frameId, m_worlds, &frameType ));
        assert( frameType == FrameType::Kinematic );
        return result;
    }

    IFramePart* Physics::getFramePart( FramePartID _framePartId ) 
    {
        return const_cast<IFramePart*>(internalGetFramePart( _framePartId, m_worlds ));
    }

    const IFramePart* Physics::getFramePart( FramePartID _framePartId ) const
    {
        return internalGetFramePart( _framePartId, m_worlds );
    }

    FrameBody* Physics::getFrameBody( FramePartID _framePartId ) 
    {
        FramePartType framePartType = FramePartType::Invalid;

        const FrameBody* result = static_cast<const FrameBody*>(internalGetFramePart( _framePartId, m_worlds, &framePartType ));
        assert( framePartType == FramePartType::Body );

        return const_cast<FrameBody*>(result);
    }

    const FrameBody* Physics::getFrameBody( FramePartID _framePartId ) const
    {
        FramePartType framePartType = FramePartType::Invalid;

        const FrameBody* result = static_cast<const FrameBody*>(internalGetFramePart( _framePartId, m_worlds, &framePartType ));
        assert( framePartType == FramePartType::Body );

        return result;
    }

    FrameTrigger* Physics::getFrameTrigger( FramePartID _framePartId ) 
    {
        FramePartType framePartType = FramePartType::Invalid;

        const FrameTrigger* result = static_cast<const FrameTrigger*>(internalGetFramePart( _framePartId, m_worlds, &framePartType ));
        assert( framePartType == FramePartType::Trigger );

        return const_cast<FrameTrigger*>(result);
    }

    const FrameTrigger* Physics::getFrameTrigger( FramePartID _framePartId ) const
    {
        FramePartType framePartType = FramePartType::Invalid;

        const FrameTrigger* result = static_cast<const FrameTrigger*>(internalGetFramePart( _framePartId, m_worlds, &framePartType ));
        assert( framePartType == FramePartType::Trigger );

        return result;
    }

    FrameType Physics::getFrameType( FrameID _frameId ) const
    {
        PhysicsID worldIndex = kMaxU32;
        FrameType frameType = FrameType::Invalid;
        PhysicsID frameIndex = kMaxU32;

        IdHelper::readFrameID( _frameId, worldIndex, frameType, frameIndex );

        return frameType;
    }

    FrameType Physics::getFrameType( FramePartID  _framePartId ) const
    {
        PhysicsID worldIndex = kMaxU32;
        FrameType frameType = FrameType::Invalid;
        PhysicsID frameIndex = kMaxU32;
        FramePartType framePartType = FramePartType::Invalid;
        PhysicsID framePartIndex = kMaxU32;

        IdHelper::readFramePartID( _framePartId, worldIndex, frameType, frameIndex, framePartType, framePartIndex );
        
        return frameType;
    }

    FramePartType Physics::getFramePartType( FramePartID _framePartId ) const
    {
        PhysicsID worldIndex = kMaxU32;
        FrameType frameType = FrameType::Invalid;
        PhysicsID frameIndex = kMaxU32;
        FramePartType framePartType = FramePartType::Invalid;
        PhysicsID framePartIndex = kMaxU32;

        IdHelper::readFramePartID( _framePartId, worldIndex, frameType, frameIndex, framePartType, framePartIndex );

        return framePartType;
    }
}