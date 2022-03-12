#pragma once
#include <utils/geometry/vec2.h>
#include <physics/simulation/frames/iframe.h>

namespace puma::physics
{
    class IKinematicFrame : public IFrame
    {
    public:

        virtual ~IKinematicFrame() {}

        virtual Vec2 getLinearVelocity() const = 0;
        virtual void setLinearVelocity( const Vec2& _linearVelocity ) = 0;

        virtual float getAngularVelocity() const = 0;
        virtual void setAngularVelocity( float _angularVelocity ) = 0;
    };
}