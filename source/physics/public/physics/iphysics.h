#pragma once

#include <utils/geometry/vec2.h>

namespace puma::physics
{
    class IPhysics
    {
    public:

        virtual ~IPhysics() {}

        static std::unique_ptr<IPhysics> create();

        virtual void update( float _deltaTime ) = 0;

        virtual WorldID addWorld( Vec2 _gravity ) = 0;
        virtual void removeWorld( WorldID _worldId ) = 0;

        virtual IWorld* getWorld( WorldID _worldId ) = 0;
        virtual const IWorld* getWorld( WorldID _worldId ) const = 0;

        virtual IFrame* getFrame( FrameID _frameId ) = 0;
        virtual const IFrame* getFrame( FrameID _frameId ) const = 0;

        virtual IDynamicFrame* getDynamicFrame( FrameID _frameId ) = 0;
        virtual const IDynamicFrame* getDynamicFrame( FrameID _frameId ) const = 0;
        
        virtual IStaticFrame* getStaticFrame( FrameID _frameId ) = 0;
        virtual const IStaticFrame* getStaticFrame( FrameID _frameId ) const = 0;
        
        virtual IKinematicFrame* getKinematicFrame( FrameID _frameId ) = 0;
        virtual const IKinematicFrame* getKinematicFrame( FrameID _frameId ) const = 0;

        virtual IFramePart* getFramePart( FramePartID _framePartId ) = 0;
        virtual const IFramePart* getFramePart( FramePartID _framePartId ) const = 0;
        
        virtual IFrameBody* getFrameBody( FramePartID _framePartId ) = 0;
        virtual const IFrameBody* getFrameBody( FramePartID _framePartId ) const = 0;
        
        virtual IFrameTrigger* getFrameTrigger( FramePartID _framePartId ) = 0;
        virtual const IFrameTrigger* getFrameTrigger( FramePartID _framePartId ) const = 0;

        virtual FrameType getFrameType( FrameID _frameId ) const = 0;
        virtual FrameType getFrameType( FramePartID  _framePartId ) const = 0;
        virtual FramePartType getFramePartType( FramePartID _framePartId ) const = 0;

    };
}