#include <precompiledphysics.h>

#include <internal/simulation/frameparts/frametrigger.h>

#include <physics/geometry/shapes.h>    

#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>

namespace puma::physics
{
    FrameTrigger::FrameTrigger( b2Fixture* _fixture, FramePartID _id )
        : m_framePart (_fixture, _id)
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