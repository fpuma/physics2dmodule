#pragma once
#include <leo/debug/debugdraw.h>
#include <utils/geometry/vec2.h>

namespace puma::leo
{
    struct FrameInfo;
    class ICollisionListener;

    class IWorld
    {
    public:

        virtual ~IWorld() {}

        virtual WorldID getWorldID() const = 0;

        virtual Vec2 getGravity() const = 0;
        virtual void setGravity( const Vec2& _gravity ) = 0;

        virtual const FrameID addDynamicFrame( const FrameInfo& _frameInfo ) = 0;
        virtual const FrameID addStaticFrame( const FrameInfo& _frameInfo ) = 0;
        virtual const FrameID addKinematicFrame( const FrameInfo& _frameInfo ) = 0;

        virtual IFrame* getFrame( const FrameID& _frameId ) = 0;
        virtual IDynamicFrame* getDynamicFrame( const FrameID& _frameId ) = 0;
        virtual IStaticFrame* getStaticFrame( const FrameID& _frameId ) = 0;
        virtual IKinematicFrame* getKinematicFrame( const FrameID& _frameId ) = 0;

        virtual const IFrame* getFrame( const FrameID& _frameId ) const = 0;
        virtual const IDynamicFrame* getDynamicFrame( const FrameID& _frameId ) const = 0;
        virtual const IStaticFrame* getStaticFrame( const FrameID& _frameId ) const = 0;
        virtual const IKinematicFrame* getKinematicFrame( const FrameID& _frameId ) const = 0;

        virtual void removeFrame( const FrameID& _frameId ) = 0;

        virtual void update( float _deltaTime ) = 0;

        virtual void setCollisionCompatibility( const CollisionCompatibility& _collisionCompatibility ) = 0;
        virtual CollisionMask getCollisionMask( CollisionIndex _collisionIndex ) const = 0;

        virtual void setCollisionListener( std::unique_ptr<ICollisionListener>&& _collisionListener ) = 0;

        virtual void setDebugDraw( std::unique_ptr<DebugDraw>&& _debugDraw ) = 0;
        virtual void debugDraw() = 0;
    };
}