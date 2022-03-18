#include <precompiledphysics.h>

#include "internalcollisionlistener.h"

#include <physics/collisions/collisionlistener.h>

#include <box2d/b2_contact.h>

namespace puma::leo
{

    InternalCollisionListener::InternalCollisionListener( InternalCollisionListener&& _other ) noexcept
    {
        collisionListener = std::move( _other.collisionListener );
    }

    void InternalCollisionListener::BeginContact( b2Contact* contact )
    {
        if ( nullptr != collisionListener )
        {
            collisionListener->collisionStarted( std::move( FramePartID( (PhysicsID)(u64)contact->GetFixtureA()->GetUserData().pointer ) ), std::move( FramePartID( (PhysicsID)(u64)contact->GetFixtureB()->GetUserData().pointer ) ) );
        }
    }

    void InternalCollisionListener::EndContact( b2Contact* contact )
    {
        if ( nullptr != collisionListener )
        {
            collisionListener->collisionStopped( std::move( FramePartID( (PhysicsID)(u64)contact->GetFixtureA()->GetUserData().pointer ) ), std::move( FramePartID( (PhysicsID)(u64)contact->GetFixtureB()->GetUserData().pointer ) ) );
        }
    }
}