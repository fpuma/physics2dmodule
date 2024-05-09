#pragma once

#include <leo/simulation/frameparts/iframepart.h>

namespace puma::leo
{
    class IFrameBody : public IFramePart
    {
    public:

        virtual ~IFrameBody(){}

        virtual float getFriction() const = 0;
        virtual void setFriction( float _friction ) = 0;
        
        virtual float getRestitution() const = 0;
        virtual void setRestitution( float _restitution ) = 0;
    };
}