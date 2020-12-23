#pragma once
#include <physics/simulation/frames/istaticframe.h>

#include <internal/simulation/frames/frame.h>

class b2Body;

namespace puma::physics
{
    class World;

    class StaticFrame : public IStaticFrame, public NonCopyable
    {
    public:
        StaticFrame() = delete;
        StaticFrame( b2Body* _body, const World* _world, FrameID _id );
        StaticFrame( StaticFrame&& _other ) noexcept : m_frame( std::move( _other.m_frame ) ) {}

        FrameID getID() const override { return m_frame.getID(); }

        Vec2 getPosition() const override;
        void setPosition( const Vec2& _position ) override;

        float getAngle() const override;
        void setAngle( float _angle ) override;

        void setTransform( const Vec2& _position, float _angle ) override;

        FramePartID addBody( const BodyInfo& _bodyInfo ) override;
        FramePartID addTrigger( const TriggerInfo& _triggerInfo ) override;

        IFramePart* getFramePart( const FramePartID& _framePartId ) override;
        FrameBody* getBody( const FramePartID& _framePartId ) override;
        FrameTrigger* getTrigger( const FramePartID& _framePartId ) override;

        const IFramePart* getFramePart( const FramePartID& _framePartId ) const override;
        const FrameBody* getBody( const FramePartID& _framePartId ) const override;
        const FrameTrigger* getTrigger( const FramePartID& _framePartId ) const override;

        void removeFramePart( const FramePartID& _framePartId ) override;

        bool isValid() const override;

        bool isEnabled() const override;
        void enable() override;
        void disable() override;

        //Internal=============================================================================================
        Frame* getInternalFrame() { return &m_frame; }
        const Frame* getInternalFrame() const { return &m_frame; }
        
    private:

        Frame m_frame;
    };    
}