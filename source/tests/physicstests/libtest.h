#pragma once
#include <precompiledphysics.h>
#include <graphics/iapplication.h>
#include <graphics/commondefinitions.h>

#include <leo/iphysics.h>
#include <leo/collisions/collisionlistener.h>
#include <leo/simulation/world/iworld.h>
#include <leo/simulation/frames/idynamicframe.h>
#include <leo/simulation/frames/istaticframe.h>
#include <leo/simulation/frames/frameinfo.h>
#include <leo/simulation/frameparts/iframepart.h>

#include <utils/geometry/shapes/shape.h>
#include <utils/geometry/vec2.h>

#include <bitset>
#include <iostream>

using namespace puma;
using namespace puma::leo;

using Vec2 = puma::Vec2;
//using RGBA = puma::leo::RGBA;

puma::app::Color colorTransform( const RGBA& color )
{
    return { (unsigned char)(color.r * 255.0f), (unsigned char)(color.g * 255.0f), (unsigned char)(color.b * 255.0f), (unsigned char)(color.a * 255.0f) };
}

void printIdBinary( const char* _name, PhysicsID _id )
{
    std::bitset<32> bs( _id );
    std::cout << _name << ": " << bs << std::endl;
}

class MyDebugDraw : public puma::leo::DebugDraw
{
public:

    void renderPolygon( const std::vector<Vec2>&& _vertices, const RGBA&& _color ) override
    {
        std::vector<short> xCoords( _vertices.size() );
        std::vector<short> yCoords( _vertices.size() );

        std::transform( _vertices.begin(), _vertices.end(), xCoords.begin(), []( const Vec2& _vertex )
        {
            return (short)_vertex.x;
        } );

        std::transform( _vertices.begin(), _vertices.end(), yCoords.begin(), []( const Vec2& _vertex )
        {
            return (short)_vertex.y;
        } );

        graphics->getDefaultRenderer()->renderPolygon( xCoords.data(), yCoords.data(), (int)_vertices.size(), colorTransform( _color ) );
    }

    void renderSolidPolygon( const std::vector<Vec2>&& _vertices, const RGBA&& _color ) override
    {
        std::vector<short> xCoords( _vertices.size() );
        std::vector<short> yCoords( _vertices.size() );

        std::transform( _vertices.begin(), _vertices.end(), xCoords.begin(), []( const Vec2& _vertex )
        {
            return (short)_vertex.x;
        } );

        std::transform( _vertices.begin(), _vertices.end(), yCoords.begin(), []( const Vec2& _vertex )
        {
            return (short)_vertex.y;
        } );

        graphics->getDefaultRenderer()->renderSolidPolygon( xCoords.data(), yCoords.data(), (int)_vertices.size(), colorTransform( _color ) );
    }

    void renderCircle( const Vec2&& _center, float _radius, const RGBA&& _color ) override
    {
        graphics->getDefaultRenderer()->renderCircle( (int)_center.x, (int)_center.y, (int)_radius, colorTransform( _color ) );
    }

    void renderSolidCircle( const Vec2&& _center, float _radius, const RGBA&& _color ) override
    {
        graphics->getDefaultRenderer()->renderSolidCircle( (int)_center.x, (int)_center.y, (int)_radius, colorTransform( _color ) );
    }

    void renderSegment( const Vec2&& _point1, const Vec2&& _point2, const RGBA&& _color ) override
    {
        graphics->getDefaultRenderer()->renderSegment( (int)_point1.x, (int)_point1.y, (int)_point2.x, (int)_point2.y, colorTransform( _color ) );
    }

    puma::app::IApplication* graphics = nullptr;
};

class MyCollisionListener : public ICollisionListener
{
public:
    void collisionStarted( FramePartID _framePartIdA, FramePartID _framePartIdB, ContactPoint _contactPoint ) override
    {
        std::cout << "Contact between: " << (char*)m_physics->getFramePart( _framePartIdA )->getUserData() << " and " << (char*)m_physics->getFramePart( _framePartIdB )->getUserData() << " STARTED at " << _contactPoint.x << " | " << _contactPoint.y << std::endl;
    }

    void collisionStopped( FramePartID _framePartIdA, FramePartID _framePartIdB ) override
    { 
        std::cout << "Contact between: " << (char*)m_physics->getFramePart( _framePartIdA )->getUserData() << " and " << (char*)m_physics->getFramePart( _framePartIdB )->getUserData() << " STOPPED" << std::endl;
    }

    IPhysics* m_physics = nullptr;
};

class LibTest
{
public:

    LibTest()
        : m_physics( puma::leo::IPhysics::create() ) {}

    void init( puma::app::IApplication* _graphics )
    {
        m_worldId = m_physics->addWorld( Vec2{} );
        std::unique_ptr<MyDebugDraw> dbgDraw = std::make_unique<MyDebugDraw>();
        dbgDraw->graphics = _graphics;

        std::unique_ptr<MyCollisionListener> collisionListener = std::make_unique<MyCollisionListener>();
        collisionListener->m_physics = m_physics.get();

        puma::leo::IWorld* worldPtr = m_physics->getWorld(m_worldId);
        worldPtr->setDebugDraw( std::move( dbgDraw ) );
        worldPtr->setCollisionListener( std::move( collisionListener ) );
        worldPtr->setGravity( { 0.0f, 10.0f } );
        worldPtr->setCollisionCompatibility( { {1,1}, {2,2}, {1,3}, {2,3}, {3,3} } );
        //========================================================================

        puma::leo::FrameInfo frameInfo;

        //Dynamics
        {
            puma::leo::BodyInfo circleBodyInfo;
            circleBodyInfo.shape.setAsCircle( { {}, 25.0f } );
            circleBodyInfo.density = 0.5f;

            frameInfo.position = { 50.0f , 50.0f };
            FrameID dynamicId0 = worldPtr->addDynamicFrame( frameInfo );
            IDynamicFrame* dynamic0 = m_physics->getDynamicFrame( dynamicId0 );
            circleBodyInfo.collisionIndex = 1;
            circleBodyInfo.userData = (void*)m_dynamic1str.c_str();
            dynamic0->addBody( circleBodyInfo );
            

            frameInfo.position = { 150.0f , 50.0f };
            FrameID dynamicId1 = worldPtr->addDynamicFrame( frameInfo );
            IDynamicFrame* dynamic1 = m_physics->getDynamicFrame( dynamicId1 );
            circleBodyInfo.collisionIndex = 2;
            circleBodyInfo.userData = (void*)m_dynamic2str.c_str();
            circleBodyInfo.restitution = 0.5f;
            dynamic1->addBody( circleBodyInfo );
            
        }

        //trigger
        {
            puma::leo::TriggerInfo circleTriggerInfo;
            circleTriggerInfo.shape.setAsCircle( { {}, 25.0f } );

            frameInfo.position = { 250.0f , 50.0f };
            FrameID dynamicId2 = worldPtr->addDynamicFrame( frameInfo );
            IDynamicFrame* dynamic2 = m_physics->getDynamicFrame( dynamicId2 );
            circleTriggerInfo.collisionIndex = 3;
            circleTriggerInfo.userData = (void*)m_trigger1str.c_str();
            dynamic2->addTrigger( circleTriggerInfo );
        }

        //Statics
        {
            puma::leo::BodyInfo rectangleBodyInfo;
            rectangleBodyInfo.shape.setAsPolygon( { { 130.0f, 15.0f }, { -130.0f, -15.0f } } );

            frameInfo.position = { 150.0f , 200.0f };
            FrameID staticId0 = worldPtr->addStaticFrame( frameInfo );
            IStaticFrame* static0 = m_physics->getStaticFrame( staticId0 );
            rectangleBodyInfo.collisionIndex = 1;
            rectangleBodyInfo.userData = (void*)m_static1str.c_str();
            static0->addBody( rectangleBodyInfo );

            frameInfo.position = { 150.0f , 350.0f };
            FrameID staticId1 = worldPtr->addStaticFrame( frameInfo );
            IStaticFrame* static1 = m_physics->getStaticFrame( staticId1 );
            rectangleBodyInfo.collisionIndex = 2;
            rectangleBodyInfo.userData = (void*)m_static2str.c_str();
            static1->addBody( rectangleBodyInfo );

            frameInfo.position = { 150.0f , 500.0f };
            FrameID staticId2 = worldPtr->addStaticFrame( frameInfo );
            IStaticFrame* static2 = m_physics->getStaticFrame( staticId2 );
            rectangleBodyInfo.collisionIndex = 3;
            rectangleBodyInfo.userData = (void*)m_static3str.c_str();
            static2->addBody( rectangleBodyInfo );
        }

    }

    void update()
    {
        m_physics->update( 1.0f / 60.0f );
    }

    void render()
    {
        m_physics->getWorld(m_worldId)->debugDraw();
    }

    std::unique_ptr<IPhysics> m_physics;

    std::string m_static1str = "StaticPlatform1";
    std::string m_static2str = "StaticPlatform2";
    std::string m_static3str = "StaticPlatform3";

    std::string m_dynamic1str = "DynamicCircle1";
    std::string m_dynamic2str = "DynamicCircle2";

    std::string m_trigger1str = "TriggerCircle1";

    WorldID m_worldId{ kInvalidPhysicsID };
};


