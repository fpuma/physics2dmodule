#pragma once
#include <utils/geometry/vec2.h>
#include <leo/simulation/frames/iframe.h>

#include <internal/simulation/frameparts/framebody.h>
#include <internal/simulation/frameparts/frametrigger.h>

class b2Body;

namespace puma::leo
{
    class World;

    class Frame : public NonCopyable
    {
    public:
        Frame() = delete;
        Frame( const World* _worldPtr, FrameID _frameId );
        Frame( Frame&& _other ) noexcept;
        virtual ~Frame();

        FrameID getID() const { return m_frameId; }

        Vec2 getPosition() const;
        void setPosition( const Vec2& _position );

        float getAngle() const;
        void setAngle( float _angle );

        Vec2 getLinearVelocity() const;
        void setLinearVelocity( const Vec2& _linearVelocity );

        float getAngularVelocity() const;
        void setAngularVelocity( float _angularVelocity );

        void applyForce( const Vec2& _force, const Vec2& _worldPoint );
        void applyForceToCenter( const Vec2& _force );

        void applyTorque( float _torque );

        void applyLinearImpulse( const Vec2& _impulse, const Vec2& _worldPoint );
        void applyLinearImpulseToCenter( const Vec2& _impulse );

        void applyAngularImpulse( float _impulse );

        void setTransform( const Vec2& _position, float _angle );

        FramePartID addBody( const BodyInfo& _bodyInfo );
        FramePartID addTrigger( const TriggerInfo& _triggerInfo );
        
        void removeFramePart( const FramePartID& _framePartId );

        IFramePart* getFramePart( const FramePartID& _framePartId );
        FrameBody* getBody( const FramePartID& _framePartId );
        FrameTrigger* getTrigger( const FramePartID& _framePartId );

        const IFramePart* getFramePart( const FramePartID& _framePartId ) const;
        const FrameBody* getBody( const FramePartID& _framePartId ) const;
        const FrameTrigger* getTrigger( const FramePartID& _framePartId ) const;

        bool isValid() const;

        bool isEnabled() const;
        void enable();
        void disable();

        //Internal=============================================================================================
        FramePart* getInternalFramePart( FramePartType _framePartType, PhysicsID _framePartIndex );
        const FramePart* getInternalFramePart( FramePartType _framePartType, PhysicsID _framePartIndex ) const;
        
        IFramePart* getFramePart( FramePartType _framePartType, u32 _framePartIndex );
        const IFramePart* getFramePart( FramePartType _framePartType, u32 _framePartIndex ) const;

        FrameBody* getFrameBody( PhysicsID _index )             { assert( _index < m_frameBodies.size() ); return m_frameBodies[_index].isValid() ? &m_frameBodies[_index] : nullptr; }
        const FrameBody* getFrameBody( PhysicsID _index ) const { assert( _index < m_frameBodies.size() ); return m_frameBodies[_index].isValid() ? &m_frameBodies[_index] : nullptr; }
        
        FrameTrigger* getFrameTrigger( PhysicsID _index )             { assert( _index < m_frameTriggers.size() ); return m_frameTriggers[_index].isValid() ? &m_frameTriggers[_index] : nullptr; }
        const FrameTrigger* getFrameTrigger( PhysicsID _index ) const { assert( _index < m_frameTriggers.size() ); return m_frameTriggers[_index].isValid() ? &m_frameTriggers[_index] : nullptr; }

        const b2Body* getB2Body() const { return m_b2Body; }
        b2Body* getB2Body() { return m_b2Body; }

        void setB2Body( b2Body* _body ) { m_b2Body = _body; }

    private:

        void removeFramePart( FramePart* _framePart, FramePartType _framePartType, PhysicsID _framePartIndex );

        b2Body* m_b2Body = nullptr;

        const World* m_world = nullptr;

        std::vector<FrameBody> m_frameBodies;
        std::vector<FrameTrigger> m_frameTriggers;

        u32 m_framePartCount = 0;

        FrameID m_frameId;
    };
}