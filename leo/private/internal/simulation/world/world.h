#pragma once
#include <leo/collisions/collisionlistener.h>
#include <utils/geometry/vec2.h>
#include <leo/simulation/world/iworld.h>

#include <internal/simulation/frames/dynamicframe.h>
#include <internal/simulation/frames/kinematicframe.h>
#include <internal/simulation/frames/staticframe.h>
#include <internal/simulation/world/internaldebugdraw.h>
#include <internal/simulation/world/internalcollisionlistener.h>

#include <box2d/b2_world.h>

namespace puma::leo
{
    struct FrameInfo;

    class World : public IWorld, public NonCopyable
    {
    public:
        World() = delete;
        World( World&& _world ) noexcept;
        World( Vec2 _gravity, WorldID _id );
        ~World();

        WorldID getWorldID() const override { return m_worldId; }

        void update( float _deltaTime ) override;

        Vec2 getGravity() const override;
        void setGravity( const Vec2& _gravity ) override;

        const FrameID addDynamicFrame( const FrameInfo& _frameInfo ) override;
        const FrameID addStaticFrame( const FrameInfo& _frameInfo ) override;
        const FrameID addKinematicFrame( const FrameInfo& _frameInfo ) override;

        void removeFrame( const FrameID& _frameId ) override;

        IFrame* getFrame( const FrameID& _frameId ) override;
        DynamicFrame* getDynamicFrame( const FrameID& _frameId ) override;
        StaticFrame* getStaticFrame( const FrameID& _frameId ) override;
        KinematicFrame* getKinematicFrame( const FrameID& _frameId ) override;

        const IFrame* getFrame( const FrameID& _frameId ) const override;
        const DynamicFrame* getDynamicFrame( const FrameID& _frameId ) const override;
        const StaticFrame* getStaticFrame( const FrameID& _frameId ) const override;
        const KinematicFrame* getKinematicFrame( const FrameID& _frameId ) const override;

        void setCollisionCompatibility( const CollisionCompatibility& _collisionCompatibility ) override;
        void setCollisionListener( std::unique_ptr<ICollisionListener>&& _collisionListener ) override;

        void setReuseRemovedIds(bool _reuse) { m_reuseRemovedIds = _reuse; }
        bool isReusingRemovedIds() const { return m_reuseRemovedIds; }

        void setDebugDraw( std::unique_ptr<DebugDraw>&& _debugDraw ) override;
        void debugDraw() override;

        //Internal=============================================================================================
        Frame* getInternalFrame( FrameType _frameType, u32 _frameIndex );
        const Frame* getInternalFrame( FrameType _frameType, u32 _frameIndex ) const;

        IFrame* getFrame( FrameType _frameType, u32 _frameIndex );
        const IFrame* getFrame( FrameType _frameType, u32 _frameIndex ) const;

        DynamicFrame*   getDynamicFrame( PhysicsID _index )             { assert( _index < m_dynamicFrames.size() );   return m_dynamicFrames[_index].isValid() ? &m_dynamicFrames[_index] : nullptr; }
        const DynamicFrame*   getDynamicFrame( PhysicsID _index ) const { assert( _index < m_dynamicFrames.size() );   return m_dynamicFrames[_index].isValid() ? &m_dynamicFrames[_index] : nullptr; }
        
        StaticFrame*    getStaticFrame( PhysicsID _index )             { assert( _index < m_staticFrames.size() );    return m_staticFrames[_index].isValid() ? &m_staticFrames[_index] : nullptr; }
        const StaticFrame*    getStaticFrame( PhysicsID _index ) const { assert( _index < m_staticFrames.size() );    return m_staticFrames[_index].isValid() ? &m_staticFrames[_index] : nullptr; }
        
        KinematicFrame* getKinematicFrame( PhysicsID _index )             { assert( _index < m_kinematicFrames.size() ); return m_kinematicFrames[_index].isValid() ? &m_kinematicFrames[_index] : nullptr; }
        const KinematicFrame* getKinematicFrame( PhysicsID _index ) const { assert( _index < m_kinematicFrames.size() ); return m_kinematicFrames[_index].isValid() ? &m_kinematicFrames[_index] : nullptr; }

        CollisionMask getCollisionMask( CollisionIndex _collisionIndex ) const;

    private:

        void removeFrame( Frame* _frame, FrameType _frameType, u32 _frameIndex );

        const WorldID m_worldId;

        u32 m_collisionCompatibility[kMaxCollisionCateogries] = { };
        
        InternalDebugDraw  m_internalDebugDraw;
        InternalCollisionListener m_internalCollisionListener;

        std::vector<DynamicFrame> m_dynamicFrames;
        std::vector<StaticFrame> m_staticFrames;
        std::vector<KinematicFrame> m_kinematicFrames;
        
        u32 m_frameCount = 0;
        bool m_reuseRemovedIds = true;

        b2World m_b2World;

    };


}