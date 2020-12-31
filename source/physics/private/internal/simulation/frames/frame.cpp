#include <precompiledphysics.h>

#include <internal/simulation/frames/frame.h>

#include <utils/geometry/shapes/shape.h>

#include <internal/ids/idhelper.h>
#include <internal/simulation/frames/framehelpers.h>
#include <internal/simulation/world/world.h>

#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_polygon_shape.h>

namespace puma::physics
{

    Frame::Frame( b2Body* _body, const World* _worldPtr, FrameID _frameId )
        : m_b2Body( _body )
        , m_world( _worldPtr )
        , m_frameId( _frameId )
    {
    }
    
    Frame::Frame( Frame&& _other ) noexcept
        : m_b2Body( std::move( _other.m_b2Body ) )
        , m_frameId( std::move( _other.m_frameId ) )
        , m_world( std::move( _other.m_world ) )
        , m_frameBodies( std::move( _other.m_frameBodies ) )
        , m_frameTriggers( std::move( _other.m_frameTriggers ) )
    {

    }

    Frame::~Frame()
    {

    }

    Vec2 Frame::getPosition() const 
    { 
        return { m_b2Body->GetPosition().x, m_b2Body->GetPosition().y }; 
    }

    void Frame::setPosition( const Vec2& _position )
    {
        m_b2Body->SetTransform( { _position.x, _position.y }, m_b2Body->GetAngle() );
    }

    float Frame::getAngle() const
    {
        return TO_DEGREES( m_b2Body->GetAngle() );
    }

    void Frame::setAngle( float _angle )
    {
        m_b2Body->SetTransform( m_b2Body->GetPosition(), _angle );
    }

    Vec2 Frame::getLinearVelocity() const
    {
        return Vec2{ m_b2Body->GetLinearVelocity().x, m_b2Body->GetLinearVelocity().y };
    }

    void Frame::setLinearVelocity( const Vec2& _linearVelocity )
    {
        m_b2Body->SetLinearVelocity( { _linearVelocity.x, _linearVelocity.y } );
    }

    float Frame::getAngularVelocity() const
    {
        return m_b2Body->GetAngularVelocity();
    }

    void Frame::setAngularVelocity( float _angularVelocity )
    {
        m_b2Body->SetAngularVelocity( _angularVelocity );
    }

    void Frame::applyForce( const Vec2& _force, const Vec2& _worldPoint )
    {
        m_b2Body->ApplyForce( { _force.x, _force.y }, { _worldPoint.x, _worldPoint.y }, true );
    }

    void Frame::applyForceToCenter( const Vec2& _force )
    {
        m_b2Body->ApplyForceToCenter( { _force.x, _force.y }, true );
    }

    void Frame::applyTorque( float _torque )
    {
        m_b2Body->ApplyTorque( _torque, true );
    }

    void Frame::applyLinearImpulse( const Vec2& _impulse, const Vec2& _worldPoint )
    {
        m_b2Body->ApplyLinearImpulse( { _impulse.x, _impulse.y }, { _worldPoint.x, _worldPoint.y }, true );
    }

    void Frame::applyLinearImpulseToCenter( const Vec2& _impulse )
    {
        m_b2Body->ApplyLinearImpulseToCenter( { _impulse.x, _impulse.y }, true );
    }

    void Frame::applyAngularImpulse( float _impulse )
    {
        m_b2Body->ApplyAngularImpulse( _impulse, true );
    }

    void Frame::setTransform( const Vec2& _position, float _angle )
    {
        m_b2Body->SetTransform( { _position.x, _position.y }, _angle );
    }
    
    FramePartID Frame::addBody( const BodyInfo& _bodyInfo )
    {
        assert( m_frameBodies.size() < kMaxFramePartCount );

        b2Fixture* fixture = addBodyFixture( m_b2Body, _bodyInfo, m_world->getCollisionMask( _bodyInfo.collisionIndex ) );
        
        FramePartID id( IdHelper::buildFrameBodyID( m_frameId.value(), (u32)m_frameBodies.size() ) );
        m_frameBodies.emplace_back( std::make_unique<FrameBody>( fixture, id ) );
        m_frameBodies.back()->setUserData( _bodyInfo.userData );

        fixture->GetUserData().pointer = id.value();

        return id;
    }

    FramePartID Frame::addTrigger( const TriggerInfo& _triggerInfo )
    {
        assert( m_frameTriggers.size() < kMaxFramePartCount );

        b2Fixture* fixture = addTriggerFixture( m_b2Body, _triggerInfo, m_world->getCollisionMask( _triggerInfo.collisionIndex ) );
        
        FramePartID id( IdHelper::buildFrameTriggerID( m_frameId.value(), (u32)m_frameTriggers.size() ) );
        m_frameTriggers.emplace_back( std::make_unique <FrameTrigger>( fixture, id ) );
        m_frameTriggers.back()->setUserData( _triggerInfo.userData );

        fixture->GetUserData().pointer = id.value();

        return id;
    }

    namespace
    {
        u32 getVerifiedFramePartIndex( const FramePartID& _framePartId, const FrameID& _frameId, FramePartType& _outFrameType )
        {
            PhysicsID worldIndex = kMaxU32;
            FrameType frameType = FrameType::Invalid;
            PhysicsID frameIndex = kMaxU32;
            FramePartType framePartType = FramePartType::Invalid;
            PhysicsID framePartIndex = kMaxU32;

            IdHelper::readFramePartID( _framePartId, worldIndex, frameType, frameIndex, framePartType, framePartIndex );

            PhysicsID currentWorldIndex = kMaxU32;
            FrameType currentFrameType = FrameType::Invalid;
            PhysicsID currentFrameIndex = kMaxU32;
            IdHelper::readFrameID( _frameId, currentWorldIndex, currentFrameType, currentFrameIndex );

            if ( (currentWorldIndex == worldIndex) && (currentFrameType == frameType) && (currentFrameIndex == frameIndex) )
            {
                _outFrameType = framePartType;
            }

            return frameIndex;
        }
    }

    IFramePart* Frame::getFramePart( const FramePartID& _framePartId )
    {
        FramePartType framePartType = FramePartType::Invalid;
        IFramePart* framePartPtr = nullptr;
        PhysicsID framePartIndex = getVerifiedFramePartIndex( _framePartId, m_frameId, framePartType );
        
        switch ( framePartType )
        {
        case FramePartType::Body:
            framePartPtr = getFrameBody( framePartIndex );
            break;
        case FramePartType::Trigger:
            framePartPtr = getFrameTrigger( framePartIndex );
            break;
        default:
            assert( false );
            break;
        }

        return framePartPtr;
    }

    FrameBody* Frame::getBody( const FramePartID& _framePartId )
    {
        FramePartType framePartType = FramePartType::Invalid;
        PhysicsID framePartIndex = getVerifiedFramePartIndex( _framePartId, m_frameId, framePartType );
        assert( FramePartType::Body == framePartType );
        assert( framePartIndex != kMaxU32 );
        return getFrameBody( framePartIndex );
    }

    FrameTrigger* Frame::getTrigger( const FramePartID& _framePartId )
    {
        FramePartType framePartType = FramePartType::Invalid;
        PhysicsID framePartIndex = getVerifiedFramePartIndex( _framePartId, m_frameId, framePartType );
        assert( FramePartType::Trigger == framePartType );
        assert( framePartIndex != kMaxU32 );
        return getFrameTrigger( framePartIndex );
    }

    const IFramePart* Frame::getFramePart( const FramePartID& _framePartId ) const
    {
        FramePartType framePartType = FramePartType::Invalid;
        const IFramePart* framePartPtr = nullptr;
        PhysicsID framePartIndex = getVerifiedFramePartIndex( _framePartId, m_frameId, framePartType );

        switch ( framePartType )
        {
        case FramePartType::Body:
            framePartPtr = getFrameBody( framePartIndex );
            break;
        case FramePartType::Trigger:
            framePartPtr = getFrameTrigger( framePartIndex );
            break;
        default:
            assert( false );
            break;
        }

        return framePartPtr;
    }

    const FrameBody* Frame::getBody( const FramePartID& _framePartId ) const
    {
        FramePartType framePartType = FramePartType::Invalid;
        PhysicsID framePartIndex = getVerifiedFramePartIndex( _framePartId, m_frameId, framePartType );
        assert( FramePartType::Body == framePartType );
        assert( framePartIndex != kMaxU32 );
        return getFrameBody( framePartIndex );
    }

    const FrameTrigger* Frame::getTrigger( const FramePartID& _framePartId ) const
    {
        FramePartType framePartType = FramePartType::Invalid;
        PhysicsID framePartIndex = getVerifiedFramePartIndex( _framePartId, m_frameId, framePartType );
        assert( FramePartType::Trigger == framePartType );
        assert( framePartIndex != kMaxU32 );
        return getFrameTrigger( framePartIndex );
    }

    void Frame::removeFramePart( const FramePartID& _framePartId )
    {
        PhysicsID worldIndex = kMaxU32;
        FrameType frameType = FrameType::Invalid;
        PhysicsID frameIndex = kMaxU32;
        FramePartType framePartType = FramePartType::Invalid;
        PhysicsID framePartIndex = kMaxU32;

        IdHelper::readFramePartID( _framePartId, worldIndex, frameType, frameIndex, framePartType, framePartIndex );

        FramePart* framePart = getInternalFramePart( framePartType, framePartIndex );

        m_b2Body->DestroyFixture( framePart->getB2Fixture() );
        removeFramePart( framePartType, framePartIndex );
    }

    bool Frame::isValid() const 
    { 
        return (nullptr != m_b2Body) && (nullptr != m_b2Body->GetWorld()); 
    }

    bool Frame::isEnabled() const
    {
        return m_b2Body->IsEnabled();
    }

    void Frame::enable()
    {
        m_b2Body->SetEnabled( true );
    }

    void Frame::disable()
    {
        m_b2Body->SetEnabled( false );
    }

    FramePart* Frame::getInternalFramePart( FramePartType _framePartType, PhysicsID _framePartIndex )
    {
        FramePart* framePtr = nullptr;

        switch ( _framePartType )
        {
        case FramePartType::Body:       framePtr = getFrameBody( _framePartIndex )->getInternalFramePart(); break;
        case FramePartType::Trigger:    framePtr = getFrameTrigger( _framePartIndex )->getInternalFramePart(); break;
        default: assert( false ); break;
        }

        return framePtr;
    }

    const FramePart* Frame::getInternalFramePart( FramePartType _framePartType, PhysicsID _framePartIndex ) const
    {
        const FramePart* framePtr = nullptr;

        switch ( _framePartType )
        {
        case FramePartType::Body:       framePtr = getFrameBody( _framePartIndex )->getInternalFramePart(); break;
        case FramePartType::Trigger:    framePtr = getFrameTrigger( _framePartIndex )->getInternalFramePart(); break;
        default: assert( false ); break;
        }

        return framePtr;
    }

    IFramePart* Frame::getFramePart( FramePartType _framePartType, u32 _framePartIndex )
    {
        IFramePart* framePtr = nullptr;

        switch ( _framePartType )
        {
        case FramePartType::Body:       framePtr = getFrameBody( _framePartIndex ); break;
        case FramePartType::Trigger:    framePtr = getFrameTrigger( _framePartIndex ); break;
        default: assert( false ); break;
        }

        return framePtr;
    }

    const IFramePart* Frame::getFramePart( FramePartType _framePartType, u32 _framePartIndex ) const
    {
        const IFramePart* framePtr = nullptr;

        switch ( _framePartType )
        {
        case FramePartType::Body:       framePtr = getFrameBody( _framePartIndex ); break;
        case FramePartType::Trigger:    framePtr = getFrameTrigger( _framePartIndex ); break;
        default: assert( false ); break;
        }

        return framePtr;
    }

    void Frame::removeFramePart( FramePartType _framePartType, PhysicsID _framePartIndex )
    {
        switch ( _framePartType )
        {
        case FramePartType::Body:       
        {
            assert( _framePartIndex < m_frameBodies.size() );
            m_frameBodies.erase( m_frameBodies.begin() + _framePartIndex );
            break;
        }
        case FramePartType::Trigger:    
        {
            assert( _framePartIndex < m_frameTriggers.size() );
            m_frameTriggers.erase( m_frameTriggers.begin() + _framePartIndex );
            break;
        }
        default: assert( false ); break;
        }
    }
}