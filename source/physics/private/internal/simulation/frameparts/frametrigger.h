#pragma once
#include <utils/geometry/vec2.h>
#include <physics/simulation/frameparts/iframetrigger.h>

#include <internal/simulation/frameparts/framepart.h>

class b2Fixture;

namespace puma::physics
{

    class FrameTrigger : public IFrameTrigger, public NonCopyable
    {
    public:

        FrameTrigger() = delete;
        FrameTrigger( FramePartID _id );
        FrameTrigger( FrameTrigger&& _other ) noexcept : m_framePart( std::move( _other.m_framePart ) ) {}

        float getDensity() const override;
        void setDensity( float _density ) override;

        UserCollisionData getUserData() const override { return m_framePart.getUserData(); }
        void setUserData( UserCollisionData _userData ) override { m_framePart.setUserData( _userData ); }

        FramePartID getID() const override { return m_framePart.getID(); }

        FramePartType getType() const override { return FramePartType::Trigger; }

        bool isValid() const override;

        //Internal=============================================================================================
        FramePart* getInternalFramePart() { return &m_framePart; }
        const FramePart* getInternalFramePart() const { return &m_framePart; }

    private:

        FramePart m_framePart;
    };
}