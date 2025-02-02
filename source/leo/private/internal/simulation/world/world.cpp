#include <precompiledphysics.h>

#include "world.h"

#include <leo/collisions/collisionlistener.h>
#include <leo/simulation/frames/frameinfo.h>

#include <internal/ids/idhelper.h>
#include <internal/simulation/frames/dynamicframe.h>
#include <internal/simulation/frames/staticframe.h>
#include <internal/simulation/frames/kinematicframe.h>

#include <utils/geometry/geometryhelpers.h>

#include <box2d/b2_body.h>
#include <box2d/b2_contact.h>
#include <box2d/b2_draw.h>
#include <box2d/b2_world.h>

namespace puma::leo
{
    namespace
    {
        void setBodyDef( b2BodyDef& _bodyDef, b2BodyType _bodyType, const FrameInfo& _frameInfo )
        {
            _bodyDef.type = _bodyType;
            _bodyDef.position = { _frameInfo.position.x, _frameInfo.position.y };
            _bodyDef.angle = _frameInfo.angle;
            _bodyDef.linearVelocity = { _frameInfo.linearVelocity.x, _frameInfo.linearVelocity.y };
            _bodyDef.angularVelocity = _frameInfo.angularVelocity;
            _bodyDef.linearDamping = _frameInfo.linearDamping;
            _bodyDef.angularDamping = _frameInfo.angularDamping;
            //_bodyDef.allowSleep
            //_bodyDef.awake
            _bodyDef.fixedRotation = _frameInfo.preventRotation;
            //_bodyDef.bullet
            //_bodyDef.active
            //_bodyDef.userData
            _bodyDef.gravityScale = _frameInfo.gravityScale;
        }

        template <class FrameType, class IdBuilderFunction>
        FrameType* addFrame(World* _world, std::vector<FrameType>& _frames, bool _reuseIds, IdBuilderFunction _idBuilder)
        {
            FrameType* newFrame = nullptr;

            if (_reuseIds)
            {
                auto foundIt = std::find_if(_frames.begin(), _frames.end(), [](const FrameType& frame) { return !frame.isValid(); });
                if (foundIt != _frames.end())
                {
                    newFrame = foundIt._Ptr;
                }
            }

            if (nullptr == newFrame)
            {
                FrameID id{ _idBuilder(_world->getWorldID().value(), (u32)_frames.size())};
                _frames.emplace_back(_world, id);
                newFrame = &_frames.back();
            }

            return newFrame;
        }
    }

    //World
    //******************************************

    World::World( Vec2 _gravity, WorldID _id )
        : m_worldId( _id )
        , m_b2World( b2Vec2{ _gravity.x, _gravity.y } )
    {
        m_internalDebugDraw.SetFlags( b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_aabbBit | b2Draw::e_pairBit | b2Draw::e_centerOfMassBit );
        m_b2World.SetDebugDraw( &m_internalDebugDraw );
        m_b2World.SetContactListener( &m_internalCollisionListener );
    }

    World::~World()
    {

    }

    void World::update( float _deltaTime )
    {
        m_b2World.Step( _deltaTime, 6, 2 );
    }

    Vec2 World::getGravity() const 
    { 
        return { m_b2World.GetGravity().x, m_b2World.GetGravity().y };
    }

    void World::setGravity( const Vec2& _gravity )
    {
        m_b2World.SetGravity( { _gravity.x, _gravity.y } );
    }

    const FrameID World::addDynamicFrame( const FrameInfo& _frameInfo )
    {
        assert( m_frameCount < kMaxFrameCount );

        auto foundIt = std::find_if( m_dynamicFrames.begin(), m_dynamicFrames.end(), []( const DynamicFrame& dynamicFrame ) { return !dynamicFrame.isValid(); } );

        b2BodyDef bodyDef;
        setBodyDef( bodyDef, b2_dynamicBody, _frameInfo );
        b2Body* body = m_b2World.CreateBody( &bodyDef );
        body->GetUserData().pointer = 0;

        DynamicFrame* newFrame = addFrame(this, m_dynamicFrames, m_reuseRemovedIds, IdHelper::buildDynamicFrameID);
        newFrame->getInternalFrame()->setB2Body( body );
       
        ++m_frameCount;

        return newFrame->getID();
    }

    const FrameID World::addStaticFrame( const FrameInfo& _frameInfo )
    {
        assert( m_frameCount < kMaxFrameCount );

        b2BodyDef bodyDef;
        setBodyDef( bodyDef, b2_staticBody, _frameInfo );
        b2Body* body = m_b2World.CreateBody( &bodyDef );
        body->GetUserData().pointer = 0;

        StaticFrame* newFrame = addFrame(this, m_staticFrames, m_reuseRemovedIds, IdHelper::buildStaticFrameID);
        assert(nullptr != newFrame);
        newFrame->getInternalFrame()->setB2Body( body );

        ++m_frameCount;

        return newFrame->getID();
    }

    const FrameID World::addKinematicFrame( const FrameInfo& _frameInfo )
    {
        assert( m_frameCount < kMaxFrameCount );

        auto foundIt = std::find_if( m_kinematicFrames.begin(), m_kinematicFrames.end(), []( const KinematicFrame& kinematicFrame ) { return !kinematicFrame.isValid(); } );

        b2BodyDef bodyDef;
        setBodyDef( bodyDef, b2_kinematicBody, _frameInfo );
        b2Body* body = m_b2World.CreateBody( &bodyDef );
        body->GetUserData().pointer = 0;

        KinematicFrame* newFrame = addFrame(this, m_kinematicFrames, m_reuseRemovedIds, IdHelper::buildKinematicFrameID);
        assert(nullptr != newFrame);
        newFrame->getInternalFrame()->setB2Body( body );

        ++m_frameCount;

        return newFrame->getID();
    }

    void World::removeFrame( const FrameID& _frameId )
    {
        PhysicsID worldIndex = kMaxU32;
        FrameType frameType = FrameType::Invalid;
        PhysicsID frameIndex = kMaxU32;

        IdHelper::readFrameID( _frameId, worldIndex, frameType, frameIndex );

        Frame* framePtr = getInternalFrame( frameType, frameIndex );
        
        removeFrame( framePtr, frameType, frameIndex );
        --m_frameCount;
    }

    namespace
    {
        u32 getVerifiedFrameIndex( const FrameID& _frameId, const WorldID& _worldId, FrameType& _outFrameType )
        {
            PhysicsID worldIndex = kMaxU32;
            FrameType frameType = FrameType::Invalid;
            PhysicsID frameIndex = kMaxU32;

            IdHelper::readFrameID( _frameId, worldIndex, frameType, frameIndex );

            PhysicsID currentWorldIndex = kMaxU32;
            IdHelper::readWorldID( _worldId, currentWorldIndex );

            if ( currentWorldIndex == worldIndex )
            {
                _outFrameType = frameType;
            }
            
            return frameIndex;
        }
    }

    IFrame* World::getFrame( const FrameID& _frameId )
    {
        FrameType frameType = FrameType::Invalid;
        IFrame* framePtr = nullptr;
        PhysicsID frameIndex = getVerifiedFrameIndex( _frameId, m_worldId, frameType );

        switch ( frameType )
        {
        case FrameType::Dynamic: 
            framePtr = getDynamicFrame( frameIndex );
            break;
        case FrameType::Static: 
            framePtr = getStaticFrame( frameIndex );
            break;
        case FrameType::Kinematic: 
            framePtr = getKinematicFrame( frameIndex );
            break;
        default: 
            assert( false );
            break;
        }

        return framePtr;
    }

    const IFrame* World::getFrame( const FrameID& _frameId ) const
    {
        FrameType frameType = FrameType::Invalid;
        const IFrame* framePtr = nullptr;
        PhysicsID frameIndex = getVerifiedFrameIndex( _frameId, m_worldId, frameType );

        switch ( frameType )
        {
        case FrameType::Dynamic:
            framePtr = getDynamicFrame( frameIndex );
            break;
        case FrameType::Static:
            framePtr = getStaticFrame( frameIndex );
            break;
        case FrameType::Kinematic:
            framePtr = getKinematicFrame( frameIndex );
            break;
        default:
            assert( false );
            break;
        }

        return framePtr;
    }

    DynamicFrame* World::getDynamicFrame( const FrameID& _frameId )
    {
        FrameType frameType = FrameType::Invalid;
        PhysicsID frameIndex = getVerifiedFrameIndex( _frameId, m_worldId, frameType );
        assert( FrameType::Dynamic == frameType );
        assert( frameIndex != kMaxU32 );
        return getDynamicFrame( frameIndex );
    }

    StaticFrame* World::getStaticFrame( const FrameID& _frameId )
    {
        FrameType frameType = FrameType::Invalid;
        PhysicsID frameIndex = getVerifiedFrameIndex( _frameId, m_worldId, frameType );
        assert( FrameType::Static == frameType );
        assert( frameIndex != kMaxU32 );
        return getStaticFrame( frameIndex );
    }
    
    KinematicFrame* World::getKinematicFrame( const FrameID& _frameId )
    {
        FrameType frameType = FrameType::Invalid;
        PhysicsID frameIndex = getVerifiedFrameIndex( _frameId, m_worldId, frameType );
        assert( FrameType::Kinematic == frameType );
        assert( frameIndex != kMaxU32 );
        return getKinematicFrame( frameIndex );
    }

    const DynamicFrame* World::getDynamicFrame( const FrameID& _frameId ) const
    {
        FrameType frameType = FrameType::Invalid;
        PhysicsID frameIndex = getVerifiedFrameIndex( _frameId, m_worldId, frameType );
        assert( FrameType::Dynamic == frameType );
        assert( frameIndex != kMaxU32 );
        return getDynamicFrame( frameIndex );
    }

    const StaticFrame* World::getStaticFrame( const FrameID& _frameId ) const
    {
        FrameType frameType = FrameType::Invalid;
        PhysicsID frameIndex = getVerifiedFrameIndex( _frameId, m_worldId, frameType );
        assert( FrameType::Static == frameType );
        assert( frameIndex != kMaxU32 );
        return getStaticFrame( frameIndex );
    }

    const KinematicFrame* World::getKinematicFrame( const FrameID& _frameId ) const
    {
        FrameType frameType = FrameType::Invalid;
        PhysicsID frameIndex = getVerifiedFrameIndex( _frameId, m_worldId, frameType );
        assert( FrameType::Kinematic == frameType );
        assert( frameIndex != kMaxU32 );
        return getKinematicFrame( frameIndex );
    }

    void World::setCollisionCompatibility( const CollisionCompatibility& _collisionCompatibility )
    {
        for ( const CollisionRelation& collisionRelation : _collisionCompatibility )
        {
            assert( collisionRelation.first < kMaxCollisionCateogries );
            assert( collisionRelation.second < kMaxCollisionCateogries );

            m_collisionCompatibility[collisionRelation.first]   |= (1 << collisionRelation.second);
            m_collisionCompatibility[collisionRelation.second]  |= (1 << collisionRelation.first);
        }
    }

    CollisionMask World::getCollisionMask( CollisionIndex _collisionIndex ) const
    {
        return (CollisionMask)m_collisionCompatibility[_collisionIndex];
    }

    void World::setCollisionListener( std::unique_ptr<ICollisionListener>&& _collisionListener )
    {
        assert( nullptr != _collisionListener.get() );
        m_internalCollisionListener.collisionListener = std::move( _collisionListener );
    }

    void World::setDebugDraw( std::unique_ptr<DebugDraw>&& _debugDraw )
    {
        assert( nullptr != _debugDraw.get() );
        m_internalDebugDraw.debugDraw = std::move(_debugDraw);
    }
    
    void World::debugDraw()
    {
        if ( nullptr != m_internalDebugDraw.debugDraw )
        {
            m_b2World.DebugDraw();
        }
    }

    Frame* World::getInternalFrame( FrameType _frameType, u32 _frameIndex )
    {
        Frame* framePtr = nullptr;

        switch ( _frameType )
        {
        case FrameType::Dynamic:    framePtr = getDynamicFrame( _frameIndex )   ? getDynamicFrame( _frameIndex )->getInternalFrame()   : nullptr; break;
        case FrameType::Static:     framePtr = getStaticFrame( _frameIndex )    ? getStaticFrame( _frameIndex )->getInternalFrame()    : nullptr; break;
        case FrameType::Kinematic:  framePtr = getKinematicFrame( _frameIndex ) ? getKinematicFrame( _frameIndex )->getInternalFrame() : nullptr; break;
        default: assert( false ); break;
        }

        return framePtr;
    }

    const Frame* World::getInternalFrame( FrameType _frameType, u32 _frameIndex ) const
    {
        const Frame* framePtr = nullptr;

        switch ( _frameType )
        {
        case FrameType::Dynamic:    framePtr = getDynamicFrame( _frameIndex )   ? getDynamicFrame( _frameIndex )->getInternalFrame()   : nullptr; break;
        case FrameType::Static:     framePtr = getStaticFrame( _frameIndex )    ? getStaticFrame( _frameIndex )->getInternalFrame()    : nullptr; break;
        case FrameType::Kinematic:  framePtr = getKinematicFrame( _frameIndex ) ? getKinematicFrame( _frameIndex )->getInternalFrame() : nullptr; break;
        default: assert( false ); break;
        }

        return framePtr;
    }

    IFrame* World::getFrame( FrameType _frameType, u32 _frameIndex )
    {
        IFrame* framePtr = nullptr;

        switch ( _frameType )
        {
        case FrameType::Dynamic:    framePtr = getDynamicFrame( _frameIndex ); break;
        case FrameType::Static:     framePtr = getStaticFrame( _frameIndex ); break;
        case FrameType::Kinematic:  framePtr = getKinematicFrame( _frameIndex ); break;
        default: assert( false ); break;
        }

        return framePtr;
    }

    const IFrame* World::getFrame( FrameType _frameType, u32 _frameIndex ) const
    {
        const IFrame* framePtr = nullptr;

        switch ( _frameType )
        {
        case FrameType::Dynamic:    framePtr = getDynamicFrame( _frameIndex ); break;
        case FrameType::Static:     framePtr = getStaticFrame( _frameIndex ); break;
        case FrameType::Kinematic:  framePtr = getKinematicFrame( _frameIndex ); break;
        default: assert( false ); break;
        }

        return framePtr;
    }

    void World::removeFrame( Frame* _frame, FrameType _frameType, u32 _frameIndex )
    {
        m_b2World.DestroyBody( _frame->getB2Body() );

        switch ( _frameType )
        {
        case FrameType::Dynamic:    
        {
            assert( _frameIndex < m_dynamicFrames.size() );
            m_dynamicFrames[_frameIndex].getInternalFrame()->clean();
            break;
        }
        case FrameType::Static:  
        {
            assert( _frameIndex < m_staticFrames.size() );
            m_staticFrames[_frameIndex].getInternalFrame()->clean();
            break;
        }
        case FrameType::Kinematic:  
        {
            assert( _frameIndex < m_kinematicFrames.size() );
            m_kinematicFrames[_frameIndex].getInternalFrame()->clean();
            break;
        }
        default: assert( false ); break;
        }
    }
}