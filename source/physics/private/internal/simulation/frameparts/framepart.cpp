#include <precompiledphysics.h>

#include "framepart.h"

#include <utils/geometry/shapes/shape.h>    

#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>

namespace puma::physics
{
    FramePart::FramePart( b2Fixture* _fixture, FramePartID _id )
        : m_b2Fixture (_fixture)
        , m_framePartId( { _id } )
    {
    }

    FramePart::FramePart( FramePart&& _other ) noexcept
        : m_b2Fixture( std::move( _other.m_b2Fixture ) )
        , m_userData( std::move( _other.m_userData ) )
        , m_framePartId( std::move( _other.m_framePartId ) )
    {

    }

    /*Vec2 Body::getOffset() const
    {
        return m_offset;
    }*/

    float FramePart::getFriction() const
    {
        return m_b2Fixture->GetFriction();
    }

    void FramePart::setFriction( float _friction )
    {
        m_b2Fixture->SetFriction( _friction );
    }

    float FramePart::getDensity() const
    {
        return m_b2Fixture->GetDensity();
    }

    void FramePart::setDensity( float _density )
    {
        m_b2Fixture->SetDensity( _density );
    }

    float FramePart::getRestitution() const
    {
        return m_b2Fixture->GetRestitution();
    }

    void FramePart::setRestitution( float _restitution )
    {
        m_b2Fixture->SetRestitution( _restitution );
    }

    bool FramePart::isValid() const
    { 
        return ( nullptr != m_b2Fixture ) && ( nullptr != m_b2Fixture->GetBody() ) && ( nullptr != m_b2Fixture->GetBody()->GetWorld() );
    }
}