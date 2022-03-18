#pragma once

namespace puma::leo
{
    class IFramePart
    {
    public:

        virtual ~IFramePart(){}

        virtual float getDensity() const = 0;
        virtual void setDensity( float _density ) = 0;
        
        virtual UserCollisionData getUserData() const = 0;
        virtual void setUserData( UserCollisionData _userData ) = 0;

        virtual FramePartID getID() const = 0;

        virtual FramePartType getType() const = 0;

        virtual bool isValid() const = 0;
    };
}