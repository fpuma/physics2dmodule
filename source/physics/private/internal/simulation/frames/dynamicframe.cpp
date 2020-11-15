#include <precompiledphysics.h>

#include <internal/simulation/frames/dynamicframe.h>

#include <box2d/b2_body.h>

namespace puma::physics
{
    DynamicFrame::DynamicFrame( b2Body* _body, const World* _world, FrameID _id )
        : m_frame( _body, _world, _id )
    {}
    
    //Common
    Vec2 DynamicFrame::getPosition() const
    {
        return m_frame.getPosition();
    }

    void DynamicFrame::setPosition( const Vec2& _position )
    {
        m_frame.setPosition( _position );
    }

    float DynamicFrame::getAngle() const
    {
        return m_frame.getAngle();
    }

    void DynamicFrame::setAngle( float _angle )
    {
        m_frame.setAngle( _angle );
    }

    void DynamicFrame::setTransform( const Vec2& _position, float _angle )
    {
        m_frame.setTransform( _position, _angle );
    }

    FramePartID DynamicFrame::addBody( const BodyInfo& _bodyInfo )
    {
        return m_frame.addBody( _bodyInfo );
    }
    
    FramePartID DynamicFrame::addTrigger( const TriggerInfo& _triggerInfo )
    {
        return m_frame.addTrigger( _triggerInfo );
    }

    bool DynamicFrame::isValid() const
    {
        return m_frame.isValid();
    }

    Vec2 DynamicFrame::getLinearVelocity() const
    {
        return m_frame.getLinearVelocity();
    }

    void DynamicFrame::setLinearVelocity( const Vec2& _linearVelocity )
    {
        m_frame.setLinearVelocity( { _linearVelocity.x, _linearVelocity.y } );
    }

    float DynamicFrame::getAngularVelocity() const
    {
        return m_frame.getAngularVelocity();
    }

    void DynamicFrame::setAngularVelocity( float _angularVelocity )
    {
        
        m_frame.setAngularVelocity( _angularVelocity );
    }

    void DynamicFrame::applyForce( const Vec2& _force, const Vec2& _worldPoint )
    {
        m_frame.applyForce( { _force.x, _force.y }, { _worldPoint.x, _worldPoint.y } );
    }

    void DynamicFrame::applyForceToCenter( const Vec2& _force )
    {
        m_frame.applyForceToCenter( { _force.x, _force.y } );
    }

    void DynamicFrame::applyTorque( float _torque )
    {
        m_frame.applyTorque( _torque );
    }

    void DynamicFrame::applyLinearImpulse( const Vec2& _impulse, const Vec2& _worldPoint )
    {
        m_frame.applyLinearImpulse( { _impulse.x, _impulse.y }, { _worldPoint.x, _worldPoint.y } );
    }

    void DynamicFrame::applyLinearImpulseToCenter( const Vec2& _impulse )
    {
        m_frame.applyLinearImpulseToCenter( { _impulse.x, _impulse.y } );
    }

    void DynamicFrame::applyAngularImpulse( float _impulse )
    {
        m_frame.applyAngularImpulse( _impulse );
    }
}
