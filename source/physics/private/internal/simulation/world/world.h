#pragma once
#include <physics/collisions/collisionlistener.h>
#include <physics/geometry/vec2.h>
#include <physics/simulation/world/iworld.h>

#include <internal/simulation/frames/dynamicframe.h>
#include <internal/simulation/frames/kinematicframe.h>
#include <internal/simulation/frames/staticframe.h>
#include <internal/simulation/world/internaldebugdraw.h>
#include <internal/simulation/world/internalcollisionlistener.h>

#include <box2d/b2_world.h>

namespace puma::physics
{
    struct FrameInfo;

    class World : public IWorld, public NonCopyable
    {
    public:
        World() = delete;
        World( World&& _world ) noexcept;
        World( Vec2 _gravity, WorldID _id );
        ~World();

        WorldID getWorldID() const { return m_worldId; }

        void update( float _deltaTime ) override;

        void setSimulationTimeStep( float _simulationTimeStep ) override { m_simulationTimeStep = _simulationTimeStep; }

        Vec2 getGravity() const override;
        void setGravity( const Vec2& _gravity ) override;

        const FrameID addDynamicFrame( const FrameInfo& _frameInfo ) override;
        const FrameID addStaticFrame( const FrameInfo& _frameInfo ) override;
        const FrameID addKinematicFrame( const FrameInfo& _frameInfo ) override;

        void setCollisionCompatibility( const CollisionCompatibility& _collisionCompatibility ) override;
        CollisionMask getCollisionMask( CollisionIndex _collisionIndex ) const override;
        void setCollisionListener( std::unique_ptr<ICollisionListener>&& _collisionListener ) override;

        void setDebugDraw( std::unique_ptr<DebugDraw>&& _debugDraw ) override;
        void debugDraw() override;

        //Internal
        DynamicFrame*   getDynamicFrame( PhysicsID _index )     { assert( _index < m_dynamicFrames.size() ); return &m_dynamicFrames[_index]; }
        StaticFrame*    getStaticFrame( PhysicsID _index )      { assert( _index < m_staticFrames.size() ); return &m_staticFrames[_index]; }
        KinematicFrame* getKinematicFrame( PhysicsID _index )   { assert( _index < m_kinematicFrames.size() ); return &m_kinematicFrames[_index]; }

        const DynamicFrame*     getDynamicFrame( PhysicsID _index )     const { assert( _index < m_dynamicFrames.size() ); return &m_dynamicFrames[_index]; }
        const StaticFrame*      getStaticFrame( PhysicsID _index )      const { assert( _index < m_staticFrames.size() ); return &m_staticFrames[_index]; }
        const KinematicFrame*   getKinematicFrame( PhysicsID _index )   const { assert( _index < m_kinematicFrames.size() ); return &m_kinematicFrames[_index]; }

    private:

        float m_simulationTimeStep = 1.0f / 60.0f;
        float m_timeAccumulator = 0.0f;
        
        const WorldID m_worldId;

        u32 m_collisionCompatibility[kMaxCollisionCateogries] = { };
        
        InternalDebugDraw  m_internalDebugDraw;
        InternalCollisionListener m_internalCollisionListener;

        std::vector<DynamicFrame> m_dynamicFrames;
        std::vector<StaticFrame> m_staticFrames;
        std::vector<KinematicFrame> m_kinematicFrames;
        
        b2World m_b2World;

    };


}