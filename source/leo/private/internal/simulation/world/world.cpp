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

    World::World( World&& _world ) noexcept
        : m_worldId( _world.m_worldId )
        , m_b2World( std::move(_world.m_b2World) )
        , m_internalDebugDraw ( std::move( _world.m_internalDebugDraw ) )
        , m_internalCollisionListener ( std::move(_world.m_internalCollisionListener) )
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

        DynamicFrame* newFrame;
        if ( foundIt == m_dynamicFrames.end() )
        {
            FrameID id{ IdHelper::buildDynamicFrameID( m_worldId.value(), (u32)m_dynamicFrames.size() ) };
            m_dynamicFrames.emplace_back( this, id );
            body->GetUserData().pointer = 0;
            newFrame = &m_dynamicFrames.back();

            newFrame->getInternalFrame()->setB2Body( body );
        }
        else
        {
            newFrame = foundIt._Ptr;
            newFrame->getInternalFrame()->setB2Body( body );
        }

        ++m_frameCount;

        return newFrame->getID();
    }

    const FrameID World::addStaticFrame( const FrameInfo& _frameInfo )
    {
        assert( m_frameCount < kMaxFrameCount );

        auto foundIt = std::find_if( m_staticFrames.begin(), m_staticFrames.end(), []( const StaticFrame& staticFrame ) { return !staticFrame.isValid(); } );

        b2BodyDef bodyDef;
        setBodyDef( bodyDef, b2_staticBody, _frameInfo );
        b2Body* body = m_b2World.CreateBody( &bodyDef );

        StaticFrame* newFrame;
        if ( foundIt == m_staticFrames.end() )
        {
            FrameID id{ IdHelper::buildStaticFrameID( m_worldId.value(), (u32)m_staticFrames.size() ) };
            m_staticFrames.emplace_back( this, id );
            body->GetUserData().pointer = 0;
            newFrame = &m_staticFrames.back();
            
            newFrame->getInternalFrame()->setB2Body( body );
        }
        else
        {
            newFrame = foundIt._Ptr;
            newFrame->getInternalFrame()->setB2Body( body );
        }

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

        KinematicFrame* newFrame;
        if ( foundIt == m_kinematicFrames.end() )
        {
            FrameID id{ IdHelper::buildKinematicFrameID( m_worldId.value(), (u32)m_kinematicFrames.size() ) };
            m_kinematicFrames.emplace_back( this, id );
            body->GetUserData().pointer = 0;
            newFrame = &m_kinematicFrames.back();

            newFrame->getInternalFrame()->setB2Body( body );
        }
        else
        {
            newFrame = foundIt._Ptr;
            newFrame->getInternalFrame()->setB2Body( body );
        }

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
            m_dynamicFrames[_frameIndex].getInternalFrame()->setB2Body(nullptr);
            break;
        }
        case FrameType::Static:  
        {
            assert( _frameIndex < m_staticFrames.size() );
            m_staticFrames[_frameIndex].getInternalFrame()->setB2Body( nullptr );
            break;
        }
        case FrameType::Kinematic:  
        {
            assert( _frameIndex < m_kinematicFrames.size() );
            m_kinematicFrames[_frameIndex].getInternalFrame()->setB2Body( nullptr );
            break;
        }
        default: assert( false ); break;
        }
    }
}