#pragma once
#include <physics/geometry/vec2.h>
#include <physics/simulation/frameparts/iframepart.h>

class b2Fixture;

namespace puma::physics
{

    class FramePart : public NonCopyable
    {
    public:

        FramePart() = delete;
        FramePart( b2Fixture* _fixture, FramePartID _id );
        FramePart( FramePart&& _other ) noexcept;
        virtual float getFriction() const;
        virtual void setFriction( float _friction );

        float getDensity() const;
        void setDensity( float _density );

        virtual float getRestitution() const;
        virtual void setRestitution( float _restitution );

        UserCollisionData getUserData() const { return m_userData; }
        void setUserData( UserCollisionData _userData ) { m_userData = _userData; }

        FramePartID getID() const { return m_framePartId; }

        bool isValid() const;

    private:

        b2Fixture* m_b2Fixture = nullptr;

        UserCollisionData m_userData = nullptr;

        FramePartID m_framePartId;
    };
}