#include <precompiledphysics.h>

#include "physics.h"

#include <internal/ids/ids.h>
#include <internal/ids/idhelper.h>
#include <internal/simulation/world/world.h>

#include <utils/geometry/vec2.h>

namespace puma::leo
{
    std::unique_ptr<IPhysics> IPhysics::create()
    {
        return std::make_unique<Physics>();
    }

    void Physics::update( float _deltaTime )
    {
        m_timeAccumulator += _deltaTime;
        int stepsCount = static_cast<int>(m_timeAccumulator / m_simulationTimeStep);

        if (stepsCount > 0)
        {
            m_timeAccumulator -= m_simulationTimeStep * stepsCount;

            while (stepsCount != 0)
            {
                for (WorldPtr& world : m_worlds)
                {
                    if (nullptr != world)
                    {
                        world->update( m_simulationTimeStep );
                    }
                }
                --stepsCount;
            }
        }
    }

    WorldID Physics::addWorld( Vec2 _gravity )
    {
        assert( m_worldCount < kMaxWorldCount );

        auto foundIt = std::find( m_worlds.begin(), m_worlds.end(), nullptr );

        WorldID newWorldId;

        if ( foundIt != m_worlds.end() )
        {
            s64 worldIndex = std::distance( m_worlds.begin(), foundIt );
            newWorldId = WorldID(static_cast<PhysicsID>(worldIndex));
            m_worlds[worldIndex] = std::make_unique<World>( _gravity, newWorldId );
        }
        else
        {
            newWorldId = WorldID( static_cast<PhysicsID>(m_worlds.size()) );
            m_worlds.emplace_back( std::make_unique<World>( _gravity, newWorldId ) );
        }

        ++m_worldCount;
        return newWorldId;
    }

    void Physics::removeWorld( WorldID _worldId )
    {
        auto foundIt = std::find_if( m_worlds.begin(), m_worlds.end(), [&]( const WorldPtr& _world ) { return _world->getWorldID().value() == _worldId.value(); } );
        assert( foundIt != m_worlds.end() );
        foundIt->reset( nullptr );
        --m_worldCount;
    }

    World* Physics::getWorld( WorldID _worldId )
    {
        assert( _worldId.value() < kMaxWorldCount );
        assert( _worldId.value() < m_worlds.size() );
        return m_worlds[_worldId.value()].get();
    }

    const World* Physics::getWorld( WorldID _worldId ) const
    {
        assert( _worldId.value() < kMaxWorldCount );
        assert( _worldId.value() < m_worlds.size() );
        return m_worlds[_worldId.value()].get();
    }

    namespace
    {
        const IFramePart* localGetFramePart( FramePartID _framePartId, const std::vector<WorldPtr>& _worlds, FramePartType* _outFramePartType = nullptr )
        {
            PhysicsID worldIndex = kMaxU32;
            FrameType frameType = FrameType::Invalid;
            PhysicsID frameIndex = kMaxU32;
            FramePartType framePartType = FramePartType::Invalid;
            PhysicsID framePartIndex = kMaxU32;

            IdHelper::readFramePartID( _framePartId, worldIndex, frameType, frameIndex, framePartType, framePartIndex );

            const Frame* internalFrame = _worlds[worldIndex]->getInternalFrame( frameType, frameIndex );
            const IFramePart* framePartPtr = nullptr;

            switch ( framePartType )
            {
            case FramePartType::Body:
                framePartPtr = internalFrame ? internalFrame->getFrameBody( framePartIndex ) : nullptr; 
                break;
            case FramePartType::Trigger:
                framePartPtr = internalFrame ? internalFrame->getFrameTrigger( framePartIndex ) : nullptr;
                break;
            default: assert( false ); break;
            }

            //[fpuma] This is messing with the unit tests. Replace with a log. Returning nullptr should be valid
            //assert( nullptr != framePartPtr );

            if ( nullptr != _outFramePartType )
            {
                *_outFramePartType = framePartType;
            }

            return framePartPtr;
        }
    }

    IFrame* Physics::getFrame( FrameID _frameId )
    {
        PhysicsID worldIndex = kMaxU32;
        FrameType frameType = FrameType::Invalid;
        PhysicsID frameIndex = kMaxU32;

        IdHelper::readFrameID( _frameId, worldIndex, frameType, frameIndex );
        assert( worldIndex < m_worlds.size() );

        return m_worlds[worldIndex]->getFrame( frameType, frameIndex );
    }

    const IFrame* Physics::getFrame( FrameID _frameId ) const
    {
        PhysicsID worldIndex = kMaxU32;
        FrameType frameType = FrameType::Invalid;
        PhysicsID frameIndex = kMaxU32;

        IdHelper::readFrameID( _frameId, worldIndex, frameType, frameIndex );
        assert( worldIndex < m_worlds.size() );

        return m_worlds[worldIndex]->getFrame( frameType, frameIndex );
    }

    DynamicFrame* Physics::getDynamicFrame( FrameID _frameId ) 
    {
        PhysicsID worldIndex = kMaxU32;
        FrameType frameType = FrameType::Invalid;
        PhysicsID frameIndex = kMaxU32;

        IdHelper::readFrameID( _frameId, worldIndex, frameType, frameIndex );

        assert( worldIndex < m_worlds.size() );
        assert( frameType == FrameType::Dynamic );

        return m_worlds[worldIndex]->getDynamicFrame( frameIndex );
    }

    const DynamicFrame* Physics::getDynamicFrame( FrameID _frameId ) const
    {
        PhysicsID worldIndex = kMaxU32;
        FrameType frameType = FrameType::Invalid;
        PhysicsID frameIndex = kMaxU32;

        IdHelper::readFrameID( _frameId, worldIndex, frameType, frameIndex );

        assert( worldIndex < m_worlds.size() );
        assert( frameType == FrameType::Dynamic );

        return m_worlds[worldIndex]->getDynamicFrame( frameIndex );
    }

    StaticFrame* Physics::getStaticFrame( FrameID _frameId ) 
    {
        PhysicsID worldIndex = kMaxU32;
        FrameType frameType = FrameType::Invalid;
        PhysicsID frameIndex = kMaxU32;

        IdHelper::readFrameID( _frameId, worldIndex, frameType, frameIndex );

        assert( worldIndex < m_worlds.size() );
        assert( frameType == FrameType::Static );

        return m_worlds[worldIndex]->getStaticFrame( frameIndex );
    }

    const StaticFrame* Physics::getStaticFrame( FrameID _frameId ) const
    {
        PhysicsID worldIndex = kMaxU32;
        FrameType frameType = FrameType::Invalid;
        PhysicsID frameIndex = kMaxU32;

        IdHelper::readFrameID( _frameId, worldIndex, frameType, frameIndex );

        assert( worldIndex < m_worlds.size() );
        assert( frameType == FrameType::Static );

        return m_worlds[worldIndex]->getStaticFrame( frameIndex );
    }

    KinematicFrame* Physics::getKinematicFrame( FrameID _frameId ) 
    {
        PhysicsID worldIndex = kMaxU32;
        FrameType frameType = FrameType::Invalid;
        PhysicsID frameIndex = kMaxU32;

        IdHelper::readFrameID( _frameId, worldIndex, frameType, frameIndex );

        assert( worldIndex < m_worlds.size() );
        assert( frameType == FrameType::Kinematic );

        return m_worlds[worldIndex]->getKinematicFrame( frameIndex );
    }

    const KinematicFrame* Physics::getKinematicFrame( FrameID _frameId ) const
    {
        PhysicsID worldIndex = kMaxU32;
        FrameType frameType = FrameType::Invalid;
        PhysicsID frameIndex = kMaxU32;

        IdHelper::readFrameID( _frameId, worldIndex, frameType, frameIndex );

        assert( worldIndex < m_worlds.size() );
        assert( frameType == FrameType::Kinematic );

        return m_worlds[worldIndex]->getKinematicFrame( frameIndex );
    }

    IFramePart* Physics::getFramePart( FramePartID _framePartId ) 
    {
        return const_cast<IFramePart*>(localGetFramePart( _framePartId, m_worlds ));
    }

    const IFramePart* Physics::getFramePart( FramePartID _framePartId ) const
    {
        return localGetFramePart( _framePartId, m_worlds );
    }

    FrameBody* Physics::getFrameBody( FramePartID _framePartId ) 
    {
        FramePartType framePartType = FramePartType::Invalid;

        const FrameBody* result = static_cast<const FrameBody*>(localGetFramePart( _framePartId, m_worlds, &framePartType ));
        assert( framePartType == FramePartType::Body );

        return const_cast<FrameBody*>(result);
    }

    const FrameBody* Physics::getFrameBody( FramePartID _framePartId ) const
    {
        FramePartType framePartType = FramePartType::Invalid;

        const FrameBody* result = static_cast<const FrameBody*>(localGetFramePart( _framePartId, m_worlds, &framePartType ));
        assert( framePartType == FramePartType::Body );

        return result;
    }

    FrameTrigger* Physics::getFrameTrigger( FramePartID _framePartId ) 
    {
        FramePartType framePartType = FramePartType::Invalid;

        const FrameTrigger* result = static_cast<const FrameTrigger*>(localGetFramePart( _framePartId, m_worlds, &framePartType ));
        assert( framePartType == FramePartType::Trigger );

        return const_cast<FrameTrigger*>(result);
    }

    const FrameTrigger* Physics::getFrameTrigger( FramePartID _framePartId ) const
    {
        FramePartType framePartType = FramePartType::Invalid;

        const FrameTrigger* result = static_cast<const FrameTrigger*>(localGetFramePart( _framePartId, m_worlds, &framePartType ));
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