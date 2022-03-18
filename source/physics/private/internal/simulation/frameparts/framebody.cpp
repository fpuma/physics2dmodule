#include <precompiledphysics.h>

#include "framebody.h"

#include <utils/geometry/shapes/shape.h>    

#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>

namespace puma::leo
{
    FrameBody::FrameBody( FramePartID _id )
        : m_framePart( _id )
    {
    }

    /*Vec2 Body::getOffset() const
    {
        return m_offset;
    }*/

    float FrameBody::getFriction() const
    {
        return m_framePart.getFriction();
    }

    void FrameBody::setFriction( float _friction )
    {
        m_framePart.setFriction( _friction );
    }

    float FrameBody::getDensity() const
    {
        return m_framePart.getDensity();
    }

    void FrameBody::setDensity( float _density )
    {
        m_framePart.setDensity( _density );
    }

    float FrameBody::getRestitution() const
    {
        return m_framePart.getRestitution();
    }

    void FrameBody::setRestitution( float _restitution )
    {
        m_framePart.setRestitution( _restitution );
    }

    bool FrameBody::isValid() const
    { 
        return m_framePart.isValid();
    }
}