#pragma once
#include <physics/geometry/vec2.h>
#include <physics/simulation/frames/iframe.h>

namespace puma::physics
{
    class IDynamicFrame : public IFrame
    {
    public:

        virtual ~IDynamicFrame() {}

        virtual Vec2 getLinearVelocity() const = 0;
        virtual void setLinearVelocity( const Vec2& _linearVelocity ) = 0;

        virtual float getAngularVelocity() const = 0;
        virtual void setAngularVelocity( float _angularVelocity ) = 0;

        virtual void applyForce( const Vec2& _force, const Vec2& _worldPoint ) = 0;
        virtual void applyForceToCenter( const Vec2& _force ) = 0;

        virtual void applyTorque( float _torque ) = 0;

        virtual void applyLinearImpulse( const Vec2& _impulse, const Vec2& _worldPoint ) = 0;
        virtual void applyLinearImpulseToCenter( const Vec2& _impulse ) = 0;

        virtual void applyAngularImpulse( float _impulse ) = 0;
    };
}