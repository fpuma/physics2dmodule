#pragma once
#include <utils/geometry/vec2.h>
#include <physics/simulation/frameparts/iframebody.h>

#include <internal/simulation/frameparts/framepart.h>

class b2Fixture;

namespace puma::physics
{

    class FrameBody : public IFrameBody, public NonCopyable
    {
    public:

        FrameBody() = delete;
        FrameBody( FramePartID _id );
        FrameBody( FrameBody&& _other ) noexcept : m_framePart( std::move( _other.m_framePart ) ) {}
        float getFriction() const override;
        void setFriction( float _friction ) override;

        float getDensity() const override;
        void setDensity( float _density ) override;

        float getRestitution() const override;
        void setRestitution( float _restitution ) override;

        UserCollisionData getUserData() const override { return m_framePart.getUserData(); }
        void setUserData( UserCollisionData _userData ) override { m_framePart.setUserData( _userData ); }

        FramePartID getID() const { return m_framePart.getID(); }

        FramePartType getType() const override { return FramePartType::Body; }

        bool isValid() const override;

        //Internal=============================================================================================
        FramePart* getInternalFramePart() { return &m_framePart; }
        const FramePart* getInternalFramePart() const { return &m_framePart; }

    private:

        FramePart m_framePart;

    };
}