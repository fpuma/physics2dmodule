#pragma once

#include <box2d/b2_world_callbacks.h>

class b2Contact;

namespace puma::physics
{
    class ICollisionListener;

    class InternalCollisionListener : public b2ContactListener, public NonCopyable
    {
    public:
        InternalCollisionListener() {}
        InternalCollisionListener( InternalCollisionListener&& _other ) noexcept;

        void BeginContact( b2Contact* contact ) override;
        void EndContact( b2Contact* contact ) override;

        std::unique_ptr<ICollisionListener> collisionListener = nullptr;

    };
}