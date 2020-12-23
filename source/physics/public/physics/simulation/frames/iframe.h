#pragma once
#include <physics/simulation/frameparts/bodyinfo.h>
#include <physics/simulation/frameparts/triggerinfo.h>
#include <physics/geometry/vec2.h>

namespace puma::physics
{

    class IFrame
    {
    public:

        virtual ~IFrame() {}

        virtual FrameID getID() const = 0;

        virtual Vec2 getPosition() const = 0;
        virtual void setPosition( const Vec2& _position ) = 0;

        virtual float getAngle() const = 0;
        virtual void setAngle( float _angle ) = 0;

        virtual void setTransform( const Vec2& _position, float _angle ) = 0;

        virtual FramePartID addBody( const BodyInfo& _bodyInfo ) = 0;
        virtual FramePartID addTrigger( const TriggerInfo& _triggerInfo ) = 0;

        virtual IFramePart* getFramePart( const FramePartID& _framePartId ) = 0;
        virtual IFrameBody* getBody( const FramePartID& _framePartId ) = 0;
        virtual IFrameTrigger* getTrigger( const FramePartID& _framePartId ) = 0;

        virtual const IFramePart* getFramePart( const FramePartID& _framePartId ) const = 0;
        virtual const IFrameBody* getBody( const FramePartID& _framePartId ) const = 0;
        virtual const IFrameTrigger* getTrigger( const FramePartID& _framePartId ) const = 0;

        virtual void removeFramePart( const FramePartID& _framePartId ) = 0;

        virtual bool isValid() const = 0;
        
        virtual bool isEnabled() const = 0;
        virtual void enable() = 0;
        virtual void disable() = 0;
    };
}