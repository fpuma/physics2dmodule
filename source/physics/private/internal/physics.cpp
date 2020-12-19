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

    IFrame* Physics::getFrame( FrameID _frameId )
    {
        PhysicsID worldIndex = kMaxU32;
        FrameType frameType = FrameType::Invalid;
        PhysicsID frameIndex = kMaxU32;
        
        IdHelper::readFrameID( _frameId, worldIndex, frameType, frameIndex );

        IFrame* framePtr = nullptr;
        
        switch ( frameType )
        {
        case FrameType::Dynamic:    framePtr = m_worlds[worldIndex].getDynamicFrame( frameIndex ); break;
        case FrameType::Static:     framePtr = m_worlds[worldIndex].getStaticFrame( frameIndex ); break;
        case FrameType::Kinematic:  framePtr = m_worlds[worldIndex].getKinematicFrame( frameIndex ); break;
        default: assert( false ); break;
        }

        return framePtr;
    }

    const IFrame* Physics::getFrame( FrameID _frameId ) const
    {
        PhysicsID worldIndex = kMaxU32;
        FrameType frameType = FrameType::Invalid;
        PhysicsID frameIndex = kMaxU32;

        IdHelper::readFrameID( _frameId, worldIndex, frameType, frameIndex );

        const IFrame* framePtr = nullptr;

        switch ( frameType )
        {
        case FrameType::Dynamic:    framePtr = m_worlds[worldIndex].getDynamicFrame( frameIndex ); break;
        case FrameType::Static:     framePtr = m_worlds[worldIndex].getStaticFrame( frameIndex ); break;
        case FrameType::Kinematic:  framePtr = m_worlds[worldIndex].getKinematicFrame( frameIndex ); break;
        default: assert( false ); break;
        }

        assert( nullptr != framePtr );

        return framePtr;
    }

    DynamicFrame* Physics::getDynamicFrame( FrameID _frameId ) 
    {
        PhysicsID worldIndex = kMaxU32;
        FrameType frameType = FrameType::Invalid;
        PhysicsID frameIndex = kMaxU32;

        IdHelper::readFrameID( _frameId, worldIndex, frameType, frameIndex );

        assert( frameType == FrameType::Dynamic );

        return m_worlds[worldIndex].getDynamicFrame( frameIndex );
    }

    const DynamicFrame* Physics::getDynamicFrame( FrameID _frameId ) const
    {
        PhysicsID worldIndex = kMaxU32;
        FrameType frameType = FrameType::Invalid;
        PhysicsID frameIndex = kMaxU32;

        IdHelper::readFrameID( _frameId, worldIndex, frameType, frameIndex );

        assert( frameType == FrameType::Dynamic );

        return m_worlds[worldIndex].getDynamicFrame( frameIndex );
    }

    StaticFrame* Physics::getStaticFrame( FrameID _frameId ) 
    {
        PhysicsID worldIndex = kMaxU32;
        FrameType frameType = FrameType::Invalid;
        PhysicsID frameIndex = kMaxU32;

        IdHelper::readFrameID( _frameId, worldIndex, frameType, frameIndex );

        assert( frameType == FrameType::Static );

        return m_worlds[worldIndex].getStaticFrame( frameIndex );
    }

    const StaticFrame* Physics::getStaticFrame( FrameID _frameId ) const
    {
        PhysicsID worldIndex = kMaxU32;
        FrameType frameType = FrameType::Invalid;
        PhysicsID frameIndex = kMaxU32;

        IdHelper::readFrameID( _frameId, worldIndex, frameType, frameIndex );

        assert( frameType == FrameType::Static );

        return m_worlds[worldIndex].getStaticFrame( frameIndex );
    }

    KinematicFrame* Physics::getKinematicFrame( FrameID _frameId ) 
    {
        PhysicsID worldIndex = kMaxU32;
        FrameType frameType = FrameType::Invalid;
        PhysicsID frameIndex = kMaxU32;

        IdHelper::readFrameID( _frameId, worldIndex, frameType, frameIndex );

        assert( frameType == FrameType::Kinematic );

        return m_worlds[worldIndex].getKinematicFrame( frameIndex );
    }

    const KinematicFrame* Physics::getKinematicFrame( FrameID _frameId ) const
    {
        PhysicsID worldIndex = kMaxU32;
        FrameType frameType = FrameType::Invalid;
        PhysicsID frameIndex = kMaxU32;

        IdHelper::readFrameID( _frameId, worldIndex, frameType, frameIndex );

        assert( frameType == FrameType::Kinematic );

        return m_worlds[worldIndex].getKinematicFrame( frameIndex );
    }


    IFramePart* Physics::getFramePart( FramePartID _framePartId ) 
    {
        PhysicsID worldIndex = kMaxU32;
        FrameType frameType = FrameType::Invalid;
        PhysicsID frameIndex = kMaxU32;
        FramePartType framePartType = FramePartType::Count;
        PhysicsID framePartIndex = kMaxU32;

        IdHelper::readFramePartID( _framePartId, worldIndex, frameType, frameIndex, framePartType, framePartIndex );

        IFramePart* framePartPtr = nullptr;

        switch ( framePartType )
        {
        case FramePartType::Body:
            switch ( frameType )
            {
            case FrameType::Dynamic:    framePartPtr = m_worlds[worldIndex].getDynamicFrame( frameIndex )->getFrameBody( framePartIndex ); break;
            case FrameType::Static:     framePartPtr = m_worlds[worldIndex].getStaticFrame( frameIndex )->getFrameBody( framePartIndex ); break;
            case FrameType::Kinematic:  framePartPtr = m_worlds[worldIndex].getKinematicFrame( frameIndex )->getFrameBody( framePartIndex ); break;
            default: assert( false ); break;
            }
            break;
        case FramePartType::Trigger:
            switch ( frameType )
            {
            case FrameType::Dynamic:    framePartPtr = m_worlds[worldIndex].getDynamicFrame( frameIndex )->getFrameTrigger( framePartIndex ); break;
            case FrameType::Static:     framePartPtr = m_worlds[worldIndex].getStaticFrame( frameIndex )->getFrameTrigger( framePartIndex ); break;
            case FrameType::Kinematic:  framePartPtr = m_worlds[worldIndex].getKinematicFrame( frameIndex )->getFrameTrigger( framePartIndex ); break;
            default: assert( false ); break;
            }
            break;
        default: assert( false ); break;
        }
        
        assert( nullptr != framePartPtr );

        return framePartPtr;
    }

    const IFramePart* Physics::getFramePart( FramePartID _framePartId ) const
    {
        PhysicsID worldIndex = kMaxU32;
        FrameType frameType = FrameType::Invalid;
        PhysicsID frameIndex = kMaxU32;
        FramePartType framePartType = FramePartType::Count;
        PhysicsID framePartIndex = kMaxU32;

        IdHelper::readFramePartID( _framePartId, worldIndex, frameType, frameIndex, framePartType, framePartIndex );

        const IFramePart* framePartPtr = nullptr;

        switch ( framePartType )
        {
        case FramePartType::Body:
            switch ( frameType )
            {
            case FrameType::Dynamic:    framePartPtr = m_worlds[worldIndex].getDynamicFrame( frameIndex )->getFrameBody( framePartIndex ); break;
            case FrameType::Static:     framePartPtr = m_worlds[worldIndex].getStaticFrame( frameIndex )->getFrameBody( framePartIndex ); break;
            case FrameType::Kinematic:  framePartPtr = m_worlds[worldIndex].getKinematicFrame( frameIndex )->getFrameBody( framePartIndex ); break;
            default: assert( false ); break;
            }
            break;
        case FramePartType::Trigger:
            switch ( frameType )
            {
            case FrameType::Dynamic:    framePartPtr = m_worlds[worldIndex].getDynamicFrame( frameIndex )->getFrameTrigger( framePartIndex ); break;
            case FrameType::Static:     framePartPtr = m_worlds[worldIndex].getStaticFrame( frameIndex )->getFrameTrigger( framePartIndex ); break;
            case FrameType::Kinematic:  framePartPtr = m_worlds[worldIndex].getKinematicFrame( frameIndex )->getFrameTrigger( framePartIndex ); break;
            default: assert( false ); break;
            }
            break;
        default: assert( false ); break;
        }

        assert( nullptr != framePartPtr );

        return framePartPtr;
    }

    FrameBody* Physics::getFrameBody( FramePartID _framePartId ) 
    {
        PhysicsID worldIndex = kMaxU32;
        FrameType frameType = FrameType::Invalid;
        PhysicsID frameIndex = kMaxU32;
        FramePartType framePartType = FramePartType::Count;
        PhysicsID framePartIndex = kMaxU32;

        IdHelper::readFramePartID( _framePartId, worldIndex, frameType, frameIndex, framePartType, framePartIndex );

        assert( FramePartType::Body == framePartType );

        FrameBody* frameBodyPtr = nullptr;

        switch ( frameType )
        {
        case FrameType::Dynamic:    frameBodyPtr = m_worlds[worldIndex].getDynamicFrame( frameIndex )->getFrameBody( framePartIndex ); break;
        case FrameType::Static:     frameBodyPtr = m_worlds[worldIndex].getStaticFrame( frameIndex )->getFrameBody( framePartIndex ); break;
        case FrameType::Kinematic:  frameBodyPtr = m_worlds[worldIndex].getKinematicFrame( frameIndex )->getFrameBody( framePartIndex ); break;
        default: assert( false ); break;
        }

        return frameBodyPtr;
    }

    const FrameBody* Physics::getFrameBody( FramePartID _framePartId ) const
    {
        PhysicsID worldIndex = kMaxU32;
        FrameType frameType = FrameType::Invalid;
        PhysicsID frameIndex = kMaxU32;
        FramePartType framePartType = FramePartType::Count;
        PhysicsID framePartIndex = kMaxU32;

        IdHelper::readFramePartID( _framePartId, worldIndex, frameType, frameIndex, framePartType, framePartIndex );

        assert( FramePartType::Body == framePartType );

        const FrameBody* frameBodyPtr = nullptr;

        switch ( frameType )
        {
        case FrameType::Dynamic:    frameBodyPtr = m_worlds[worldIndex].getDynamicFrame( frameIndex )->getFrameBody( framePartIndex ); break;
        case FrameType::Static:     frameBodyPtr = m_worlds[worldIndex].getStaticFrame( frameIndex )->getFrameBody( framePartIndex ); break;
        case FrameType::Kinematic:  frameBodyPtr = m_worlds[worldIndex].getKinematicFrame( frameIndex )->getFrameBody( framePartIndex ); break;
        default: assert( false ); break;
        }

        return frameBodyPtr;
    }

    FrameTrigger* Physics::getFrameTrigger( FramePartID _framePartId ) 
    {
        PhysicsID worldIndex = kMaxU32;
        FrameType frameType = FrameType::Invalid;
        PhysicsID frameIndex = kMaxU32;
        FramePartType framePartType = FramePartType::Count;
        PhysicsID framePartIndex = kMaxU32;

        IdHelper::readFramePartID( _framePartId, worldIndex, frameType, frameIndex, framePartType, framePartIndex );

        assert( FramePartType::Body == framePartType );

        FrameTrigger* frameTriggerPtr = nullptr;

        switch ( frameType )
        {
        case FrameType::Dynamic:    frameTriggerPtr = m_worlds[worldIndex].getDynamicFrame( frameIndex )->getFrameTrigger( framePartIndex ); break;
        case FrameType::Static:     frameTriggerPtr = m_worlds[worldIndex].getStaticFrame( frameIndex )->getFrameTrigger( framePartIndex ); break;
        case FrameType::Kinematic:  frameTriggerPtr = m_worlds[worldIndex].getKinematicFrame( frameIndex )->getFrameTrigger( framePartIndex ); break;
        default: assert( false ); break;
        }

        return frameTriggerPtr;
    }

    const FrameTrigger* Physics::getFrameTrigger( FramePartID _framePartId ) const
    {
        PhysicsID worldIndex = kMaxU32;
        FrameType frameType = FrameType::Invalid;
        PhysicsID frameIndex = kMaxU32;
        FramePartType framePartType = FramePartType::Count;
        PhysicsID framePartIndex = kMaxU32;

        IdHelper::readFramePartID( _framePartId, worldIndex, frameType, frameIndex, framePartType, framePartIndex );

        assert( FramePartType::Body == framePartType );

        const FrameTrigger* frameTriggerPtr = nullptr;

        switch ( frameType )
        {
        case FrameType::Dynamic:    frameTriggerPtr = m_worlds[worldIndex].getDynamicFrame( frameIndex )->getFrameTrigger( framePartIndex ); break;
        case FrameType::Static:     frameTriggerPtr = m_worlds[worldIndex].getStaticFrame( frameIndex )->getFrameTrigger( framePartIndex ); break;
        case FrameType::Kinematic:  frameTriggerPtr = m_worlds[worldIndex].getKinematicFrame( frameIndex )->getFrameTrigger( framePartIndex ); break;
        default: assert( false ); break;
        }

        return frameTriggerPtr;
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
        FramePartType framePartType = FramePartType::Count;
        PhysicsID framePartIndex = kMaxU32;

        IdHelper::readFramePartID( _framePartId, worldIndex, frameType, frameIndex, framePartType, framePartIndex );
        
        return frameType;
    }

    FramePartType Physics::getFramePartType( FramePartID _framePartId ) const
    {
        PhysicsID worldIndex = kMaxU32;
        FrameType frameType = FrameType::Invalid;
        PhysicsID frameIndex = kMaxU32;
        FramePartType framePartType = FramePartType::Count;
        PhysicsID framePartIndex = kMaxU32;

        IdHelper::readFramePartID( _framePartId, worldIndex, frameType, frameIndex, framePartType, framePartIndex );

        return framePartType;
    }
}