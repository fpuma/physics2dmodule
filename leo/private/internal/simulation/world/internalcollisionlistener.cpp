#include <precompiledphysics.h>

#include "internalcollisionlistener.h"

#include <leo/collisions/collisionlistener.h>

#include <box2d/b2_contact.h>

namespace puma::leo
{

    InternalCollisionListener::InternalCollisionListener( InternalCollisionListener&& _other ) noexcept
    {
        collisionListener = std::move( _other.collisionListener );
    }

    void InternalCollisionListener::BeginContact( b2Contact* _contact )
    {
        if ( nullptr != collisionListener )
        {
            b2WorldManifold manifold;
            _contact->GetWorldManifold( &manifold );
            ContactPoint contactPoint = { manifold.points[0].x, manifold.points[0].y };
            collisionListener->collisionStarted( std::move( FramePartID( (PhysicsID)(u64)_contact->GetFixtureA()->GetUserData().pointer ) ), std::move( FramePartID( (PhysicsID)(u64)_contact->GetFixtureB()->GetUserData().pointer ) ), contactPoint );
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