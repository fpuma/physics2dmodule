#include <precompiledphysics.h>

#include <internal/simulation/frames/frame.h>

#include <physics/geometry/shapes.h>

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
        return m_b2Body->GetAngle();
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
        m_frameBodies.emplace_back( fixture, id );
        m_frameBodies.back().setUserData( _bodyInfo.userData );

        fixture->GetUserData().pointer = id.value();

        return id;
    }

    FramePartID Frame::addTrigger( const TriggerInfo& _triggerInfo )
    {
        assert( m_frameTriggers.size() < kMaxFramePartCount );

        b2Fixture* fixture = addTriggerFixture( m_b2Body, _triggerInfo, m_world->getCollisionMask( _triggerInfo.collisionIndex ) );
        
        FramePartID id( IdHelper::buildFrameTriggerID( m_frameId.value(), (u32)m_frameTriggers.size() ) );
        m_frameTriggers.emplace_back( fixture, id );
        m_frameTriggers.back().setUserData( _triggerInfo.userData );

        fixture->GetUserData().pointer = id.value();

        return id;
    }

    bool Frame::isValid() const 
    { 
        return (nullptr != m_b2Body) && (nullptr != m_b2Body->GetWorld()); 
    }
}