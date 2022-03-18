#include <precompiledphysics.h>

#include "frametrigger.h"

#include <utils/geometry/shapes/shape.h>    

#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>

namespace puma::leo
{
    FrameTrigger::FrameTrigger( FramePartID _id )
        : m_framePart( _id )
    {
    }

    /*Vec2 Body::getOffset() const
    {
        return m_offset;
    }*/

    float FrameTrigger::getDensity() const
    {
        return m_framePart.getDensity();
    }

    void FrameTrigger::setDensity( float _density )
    {
        m_framePart.setDensity( _density );
    }


    bool FrameTrigger::isValid() const
    { 
        return m_framePart.isValid();
    }
}