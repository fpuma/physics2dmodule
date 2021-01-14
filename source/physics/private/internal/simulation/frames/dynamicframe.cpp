#include <precompiledphysics.h>

#include "dynamicframe.h"

#include <box2d/b2_body.h>

namespace puma::physics
{
    DynamicFrame::DynamicFrame( const World* _world, FrameID _id )
        : m_frame( _world, _id )
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

    IFramePart* DynamicFrame::getFramePart( const FramePartID& _framePartId )
    {
        return m_frame.getFramePart( _framePartId );
    }

    FrameBody* DynamicFrame::getBody( const FramePartID& _framePartId )
    {
        return m_frame.getBody( _framePartId );
    }

    FrameTrigger* DynamicFrame::getTrigger( const FramePartID& _framePartId )
    {
        return m_frame.getTrigger( _framePartId );
    }

    const IFramePart* DynamicFrame::getFramePart( const FramePartID& _framePartId ) const
    {
        return m_frame.getFramePart( _framePartId );
    }

    const FrameBody* DynamicFrame::getBody( const FramePartID& _framePartId ) const
    {
        return m_frame.getBody( _framePartId );
    }

    const FrameTrigger* DynamicFrame::getTrigger( const FramePartID& _framePartId ) const
    {
        return m_frame.getTrigger( _framePartId );
    }

    void DynamicFrame::removeFramePart( const FramePartID& _framePartId )
    {
        m_frame.removeFramePart( _framePartId );
    }

    bool DynamicFrame::isValid() const
    {
        return m_frame.isValid();
    }

    bool DynamicFrame::isEnabled() const
    {
        assert( isValid() );
        return m_frame.isEnabled();
    }

    void DynamicFrame::enable()
    {
        assert( isValid() );
        m_frame.enable();
    }

    void DynamicFrame::disable()
    {
        assert( isValid() );
        m_frame.disable();
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
