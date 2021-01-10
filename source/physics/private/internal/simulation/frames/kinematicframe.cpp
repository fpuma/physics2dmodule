#include <precompiledphysics.h>

#include "kinematicframe.h"

#include <box2d/b2_body.h>

namespace puma::physics
{
    KinematicFrame::KinematicFrame( b2Body* _body, const World* _world, FrameID _id )
        : m_frame( _body, _world, _id )
    {}

    //Common
    Vec2 KinematicFrame::getPosition() const
    {
        return m_frame.getPosition();
    }

    void KinematicFrame::setPosition( const Vec2& _position )
    {
        m_frame.setPosition( _position );
    }

    float KinematicFrame::getAngle() const
    {
        return m_frame.getAngle();
    }

    void KinematicFrame::setAngle( float _angle )
    {
        m_frame.setAngle( _angle );
    }

    void KinematicFrame::setTransform( const Vec2& _position, float _angle )
    {
        m_frame.setTransform( _position, _angle );
    }

    FramePartID KinematicFrame::addBody( const BodyInfo& _bodyInfo )
    {
        return m_frame.addBody( _bodyInfo );
    }

    FramePartID KinematicFrame::addTrigger( const TriggerInfo& _triggerInfo )
    {
        return m_frame.addTrigger( _triggerInfo );
    }

    IFramePart* KinematicFrame::getFramePart( const FramePartID& _framePartId )
    {
        return m_frame.getFramePart( _framePartId );
    }

    FrameBody* KinematicFrame::getBody( const FramePartID& _framePartId )
    {
        return m_frame.getBody( _framePartId );
    }

    FrameTrigger* KinematicFrame::getTrigger( const FramePartID& _framePartId )
    {
        return m_frame.getTrigger( _framePartId );
    }

    const IFramePart* KinematicFrame::getFramePart( const FramePartID& _framePartId ) const
    {
        return m_frame.getFramePart( _framePartId );
    }

    const FrameBody* KinematicFrame::getBody( const FramePartID& _framePartId ) const
    {
        return m_frame.getBody( _framePartId );
    }

    const FrameTrigger* KinematicFrame::getTrigger( const FramePartID& _framePartId ) const
    {
        return m_frame.getTrigger( _framePartId );
    }

    void KinematicFrame::removeFramePart( const FramePartID& _framePartId )
    {
        m_frame.removeFramePart( _framePartId );
    }

    bool KinematicFrame::isValid() const
    {
        return m_frame.isValid();
    }

    bool KinematicFrame::isEnabled() const
    {
        assert( isValid() );
        return m_frame.isEnabled();
    }

    void KinematicFrame::enable()
    {
        assert( isValid() );
        m_frame.enable();
    }

    void KinematicFrame::disable()
    {
        assert( isValid() );
        m_frame.disable();
    }

    //KinematicFrame exclusive
    Vec2 KinematicFrame::getLinearVelocity() const
    {
        return { m_frame.getLinearVelocity().x, m_frame.getLinearVelocity().y };
    }

    void KinematicFrame::setLinearVelocity( const Vec2& _linearVelocity )
    {
        m_frame.setLinearVelocity( { _linearVelocity.x, _linearVelocity.y } );
    }

    float KinematicFrame::getAngularVelocity() const
    {
        return m_frame.getAngularVelocity();
    }

    void KinematicFrame::setAngularVelocity( float _angularVelocity )
    {
        m_frame.setAngularVelocity( _angularVelocity );
    }
}