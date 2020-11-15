#pragma once
#include <physics/debug/debugdraw.h>
#include <physics/geometry/vec2.h>

namespace puma::physics
{
    struct FrameInfo;
    class ICollisionListener;

    class IWorld
    {
    public:

        virtual ~IWorld() {}

        virtual Vec2 getGravity() const = 0;
        virtual void setGravity( const Vec2& _gravity ) = 0;

        virtual const FrameID addDynamicFrame( const FrameInfo& _frameInfo ) = 0;
        virtual const FrameID addStaticFrame( const FrameInfo& _frameInfo ) = 0;
        virtual const FrameID addKinematicFrame( const FrameInfo& _frameInfo ) = 0;

        virtual void update( float _deltaTime ) = 0;

        virtual void setSimulationTimeStep( float _simulationTimeStep ) = 0;

        virtual void setCollisionCompatibility( const CollisionCompatibility& _collisionCompatibility ) = 0;
        virtual CollisionMask getCollisionMask( CollisionIndex _collisionIndex ) const = 0;

        virtual void setCollisionListener( std::unique_ptr<ICollisionListener>&& _collisionListener ) = 0;

        virtual void setDebugDraw( std::unique_ptr<DebugDraw>&& _debugDraw ) = 0;
        virtual void debugDraw() = 0;
    };
}