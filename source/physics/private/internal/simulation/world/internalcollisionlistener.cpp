#include <precompiledphysics.h>

#include <internal/simulation/world/internalcollisionlistener.h>

#include <physics/collisions/collisionlistener.h>

#include <box2d/b2_contact.h>

namespace puma::physics
{

    InternalCollisionListener::InternalCollisionListener( InternalCollisionListener&& _other ) noexcept
    {
        collisionListener = std::move( _other.collisionListener );
    }

    void InternalCollisionListener::BeginContact( b2Contact* contact )
    {
        collisionListener->collisionStarted( std::move( FramePartID( (PhysicsID)(u64)contact->GetFixtureA()->GetUserData().pointer ) ), std::move( FramePartID( (PhysicsID)(u64)contact->GetFixtureB()->GetUserData().pointer ) ) );
    }

    void InternalCollisionListener::EndContact( b2Contact* contact )
    {
        collisionListener->collisionStopped( std::move( FramePartID( (PhysicsID)(u64)contact->GetFixtureA()->GetUserData().pointer ) ), std::move( FramePartID( (PhysicsID)(u64)contact->GetFixtureB()->GetUserData().pointer ) ) );
    }
}