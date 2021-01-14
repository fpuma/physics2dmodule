#pragma once
#include <utils/geometry/vec2.h>
#include <physics/simulation/frameparts/iframepart.h>

class b2Fixture;

namespace puma::physics
{

    class FramePart : public NonCopyable
    {
    public:

        FramePart();
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

        //Internal=============================================================================================
        const b2Fixture* getB2Fixture() const { return m_b2Fixture; }
        b2Fixture* getB2Fixture() { return m_b2Fixture; }

        void init( b2Fixture* _fixture, FramePartID _id );
        void uninit();

    private:

        b2Fixture* m_b2Fixture = nullptr;

        UserCollisionData m_userData = nullptr;

        FramePartID m_framePartId;
    };
}