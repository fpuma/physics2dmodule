#include <precompiledphysics.h>

#include "framepart.h"

#include <utils/geometry/shapes/shape.h>    

#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>

namespace puma::physics
{
    FramePart::FramePart()
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
        assert( isValid() );
        return m_b2Fixture->GetFriction();
    }

    void FramePart::setFriction( float _friction )
    {
        assert( isValid() );
        m_b2Fixture->SetFriction( _friction );
    }

    float FramePart::getDensity() const
    {
        assert( isValid() );
        return m_b2Fixture->GetDensity();
    }

    void FramePart::setDensity( float _density )
    {
        assert( isValid() );
        m_b2Fixture->SetDensity( _density );
    }

    float FramePart::getRestitution() const
    {
        assert( isValid() );
        return m_b2Fixture->GetRestitution();
    }

    void FramePart::setRestitution( float _restitution )
    {
        assert( isValid() );
        m_b2Fixture->SetRestitution( _restitution );
    }

    bool FramePart::isValid() const
    { 
        return nullptr != m_b2Fixture;
    }

    void FramePart::init( b2Fixture* _fixture, FramePartID _id )
    {
        assert( !isValid() );
        m_b2Fixture = _fixture;
        m_framePartId = _id;
    }

    void FramePart::uninit()
    {
        m_b2Fixture = nullptr;
        m_framePartId.invalidate();
    }
}