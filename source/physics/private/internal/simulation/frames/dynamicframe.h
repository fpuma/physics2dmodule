#pragma once
#include <physics/simulation/frames/idynamicframe.h>
#include <internal/simulation/frames/frame.h>

class b2Body;

namespace puma::physics
{
    class World;

    class DynamicFrame : public IDynamicFrame, public NonCopyable
    {
    public:
        DynamicFrame() = delete;
        DynamicFrame( b2Body* _body, const World* _world, FrameID _id );
        DynamicFrame( DynamicFrame&& _other ) noexcept : m_frame( std::move( _other.m_frame ) ) {}
        FrameID getID() const override { return m_frame.getID(); }

        Vec2 getPosition() const override;
        void setPosition( const Vec2& _position ) override;

        float getAngle() const override;
        void setAngle( float _angle ) override;

        void setTransform( const Vec2& _position, float _angle ) override;

        FramePartID addBody( const BodyInfo& _bodyInfo ) override;

        FramePartID addTrigger( const TriggerInfo& _triggerInfo ) override;

        bool isValid() const override;

        bool isEnabled() const override;
        void enable() override;
        void disable() override;

        Vec2 getLinearVelocity() const override;
        void setLinearVelocity( const Vec2& _linearVelocity ) override;

        float getAngularVelocity() const override;
        void setAngularVelocity( float _angularVelocity ) override;

        void applyForce( const Vec2& _force, const Vec2& _worldPoint ) override;
        void applyForceToCenter( const Vec2& _force ) override;

        void applyTorque( float _torque ) override;

        void applyLinearImpulse( const Vec2& _impulse, const Vec2& _worldPoint ) override;
        void applyLinearImpulseToCenter( const Vec2& _impulse ) override;

        void applyAngularImpulse( float _impulse ) override;

        //Internal

        FrameBody* getFrameBody( PhysicsID _index ) { return m_frame.getFrameBody( _index ); }
        FrameTrigger* getFrameTrigger( PhysicsID _index ) { return m_frame.getFrameTrigger( _index ); }

        const FrameBody* getFrameBody( PhysicsID _index ) const { return m_frame.getFrameBody( _index ); }
        const FrameTrigger* getFrameTrigger( PhysicsID _index ) const { return m_frame.getFrameTrigger( _index ); }

    private:

        Frame m_frame;
    };
}