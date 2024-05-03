#pragma once
//#include "precompiledpt.h"
#include <precompiledapplication.h>

#include <box2d/b2_body.h>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_contact.h>
#include <box2d/b2_draw.h>
#include <box2d/b2_edge_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_revolute_joint.h>
#include <box2d/b2_world.h>

#include <graphics/iapplication.h>
#include <graphics/commondefinitions.h>


#include <string>
#include <stdarg.h>
#include <memory>
#include <vector>

#include <iostream>

puma::app::Color colorTransform( const b2Color& color )
{
	return { (unsigned char)(color.r * 255.0f), (unsigned char)(color.g * 255.0f), (unsigned char)(color.b * 255.0f), (unsigned char)(color.a * 255.0f) };
}

std::string FormatString( const char* _format, ... )
{
	va_list args;
	va_start( args, _format );
	int length = _vscprintf( _format, args ) + 1;
	char* buffer = new char[length];
	vsprintf_s( buffer, length, _format, args );
	std::string output( buffer );
	delete[] buffer;
	va_end( args );
	return output;
}

std::string getShapeName( b2Shape::Type _shapeType )
{
	switch ( _shapeType )
	{
	case b2Shape::e_circle:		return "Circle"; break;
	case b2Shape::e_edge:		return "Edge"; break;
	case b2Shape::e_polygon:	return "Polygon"; break;
	case b2Shape::e_chain:		return "Chain"; break;
	default: return "InvalidShape"; break;
	}
}

class TestDebugDraw : public b2Draw
{
public:

	void DrawPolygon( const b2Vec2* vertices, int32 vertexCount, const b2Color& color ) override
	{
		std::vector<short> xCoords( vertexCount );
		std::vector<short> yCoords( vertexCount );

		for ( int i = 0; i < vertexCount; ++i )
		{
			xCoords[i] = (short)vertices[i].x;
			yCoords[i] = (short)vertices[i].y;
		}
		
		graphics->getDefaultRenderer()->renderPolygon( xCoords.data(), yCoords.data(), vertexCount, colorTransform( color ) );
	}

	void DrawSolidPolygon( const b2Vec2* vertices, int32 vertexCount, const b2Color& color ) override
	{
		std::vector<short> xCoords( vertexCount );
		std::vector<short> yCoords( vertexCount );

		for ( int i = 0; i < vertexCount; ++i )
		{
			xCoords[i] = (short)vertices[i].x;
			yCoords[i] = (short)vertices[i].y;
		}

		graphics->getDefaultRenderer()->renderSolidPolygon( xCoords.data(), yCoords.data(), vertexCount, colorTransform( color ) );
	}

	void DrawCircle( const b2Vec2& center, float radius, const b2Color& color ) override
	{
		graphics->getDefaultRenderer()->renderCircle( (int)center.x, (int)center.y, (int)radius, colorTransform( color ) );
	}

	void DrawSolidCircle( const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color ) override
	{
		graphics->getDefaultRenderer()->renderSolidCircle( (int)center.x, (int)center.y, (int)radius, colorTransform( color ) );
	}

	void DrawSegment( const b2Vec2& p1, const b2Vec2& p2, const b2Color& color ) override
	{
		graphics->getDefaultRenderer()->renderSegment( (int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y, colorTransform( color ) );
	}

	void DrawTransform( const b2Transform& xf ) override
	{

	}

	void DrawPoint( const b2Vec2& p, float size, const b2Color& color ) override
	{
		graphics->getDefaultRenderer()->renderSolidCircle( (int)p.x, (int)p.y, (int)size, colorTransform( color ) );
	}

	puma::app::IApplication* graphics = nullptr;
};

class MyContactListener : public b2ContactListener
{
	void BeginContact( b2Contact* contact ) 
	{ 
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();
		
		std::string shapeNameA = getShapeName( fixtureA->GetType() );
		std::string shapeNameB = getShapeName( fixtureB->GetType() );
		
		std::cout << "FixtureA: " << shapeNameA.c_str() << std::endl;
		std::cout << "FixtureB: " << shapeNameB.c_str() << std::endl;
	}

	void EndContact( b2Contact* contact ) 
	{ 
		std::cout << "Disengage!" << std::endl;
	}

};

class Box2DTest
{
public:
	Box2DTest()
		: m_world( {0.0f, 0.0f} ) 
	{
		m_testDebugDraw.SetFlags( b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_aabbBit | b2Draw::e_pairBit | b2Draw::e_centerOfMassBit );
	}

	void init( puma::app::IApplication* _graphics )
	{
		b2Vec2 gravity( 0.0f, 0.0f );
		m_world.SetGravity( gravity );

		//DebugDraw
		m_testDebugDraw.graphics = _graphics;
		m_world.SetDebugDraw( &m_testDebugDraw );

		//===========================================

		//Bodies
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set( 100, 100.0f );
		//bodyDef.linearDamping = 0.5f;
		body1 = m_world.CreateBody( &bodyDef );

		bodyDef.position.Set( 200.0f, 100.0f );
		bodyDef.type = b2_staticBody;
		body2 = m_world.CreateBody( &bodyDef );

		//Shapes
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox( 25.0f, 25.0f );
		dynamicBox.m_vertices;

		b2CircleShape circleShape;
		circleShape.m_radius = 25.0f;

		//Fixtures
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		fixtureDef.filter.categoryBits = 0x01;
		fixtureDef.filter.maskBits = 0x01;
		fixtureDef.density = 0.01f;
		fixtureDef.friction = 0.3f;

		body1->CreateFixture( &fixtureDef );

		fixtureDef.shape = &circleShape;
		fixtureDef.filter.categoryBits = 0x01;
		fixtureDef.filter.maskBits = 0x01;
		body2->CreateFixture( &fixtureDef );

		//body1->SetLinearVelocity( m_velocity );
		body1->ApplyLinearImpulseToCenter( m_force, true );

		/*body1->ApplyLinearImpulseToCenter( m_force, true );
		body1->ApplyLinearImpulseToCenter( { 0.0f, 500.0f }, true );*/

		m_world.SetContactListener( &m_contactListener );
	}

	void update()
	{
		m_world.Step( timeStep, velocityIterations, positionIterations );
		m_debugInfo = FormatString( "Mass: %.2f Kg | X: %0.5f , Y: %0.5f", body1->GetMass(), body1->GetPosition().x, body1->GetPosition().y );
		//body1->ApplyForceToCenter( m_force, true );
	}

	void render()
	{
		m_world.DebugDraw();
	}

	b2World m_world;
	b2Body* body1 = nullptr;
	b2Body* body2 = nullptr;
	b2Vec2 m_force = { 500.0f, 0.0f };
	b2Vec2 m_velocity = { 10.0f, 0.0f };

	std::string m_debugInfo;
	TestDebugDraw m_testDebugDraw;
	MyContactListener m_contactListener;

	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
};

class Test2
{
public:

	Test2()
		: m_world( {0.0f, 0.0f} )
	{
		m_testDebugDraw.SetFlags( b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_aabbBit | b2Draw::e_pairBit | b2Draw::e_centerOfMassBit );
	}

	void init( puma::app::IApplication* _graphics )
	{
		b2Vec2 gravity( 0.0f, 0.0f );
		m_world.SetGravity( gravity );

		//DebugDraw
		m_testDebugDraw.graphics = _graphics;
		m_world.SetDebugDraw( &m_testDebugDraw );

		//===========================================

		//Bodies
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set( 400, 400.0f );
		body = m_world.CreateBody( &bodyDef );

		bodyDef.type = b2_staticBody;
		bodyDef.position.Set( 400, 405.0f );

		anchor = m_world.CreateBody( &bodyDef );

		//Shapes
		b2CircleShape circleShape;
		circleShape.m_radius = 10.0f;
		circleShape.m_p = { -20.0f , 0.0f };

		b2EdgeShape edgeShape;
		//edgeShape.Set( { -3.0f, 0.0f }, { 3.0f, 0.0f } );

		//Fixtures
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &circleShape;
		fixtureDef.density = 0.01f;
		fixtureDef.friction = 0.0f;

		body->CreateFixture( &fixtureDef );

		circleShape.m_p = { 20.0f , 0.0f };
		body->CreateFixture( &fixtureDef );

		circleShape.m_p = { 0.0f , 0.0f };
		circleShape.m_radius = 0.5f;
		body->CreateFixture( &fixtureDef );

		fixtureDef.shape = &edgeShape;
		anchor->CreateFixture( &fixtureDef );

		b2Vec2 forceApplicationPoint = body->GetPosition() + b2Vec2{ 200.0f, 0.0f };
		body->ApplyLinearImpulse( m_force, forceApplicationPoint, true );
		//body->ApplyLinearImpulseToCenter( m_force, true );
	}

	void update()
	{
		m_world.Step( timeStep, velocityIterations, positionIterations );
		m_debugInfo = FormatString( "Mass: %.2f Kg | X: %0.5f , Y: %0.5f", body->GetMass(), body->GetPosition().x, body->GetPosition().y );

		//body1->ApplyForceToCenter( m_force, true );
	}

	void render()
	{
		m_world.DebugDraw();
	}

	b2Body* body = nullptr;
	b2Body* anchor = nullptr;
	b2Vec2 m_force = { 0.0f, 50.0f };

	std::string m_debugInfo;
	TestDebugDraw m_testDebugDraw;
	b2World m_world;

	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
};

class Test3
{
public:

	Test3()
		: m_world( { 0.0f, 0.0f } )
	{
		m_testDebugDraw.SetFlags( b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_aabbBit | b2Draw::e_pairBit | b2Draw::e_centerOfMassBit );
	}

	void init( puma::app::IApplication* _graphics )
	{
		b2Vec2 gravity( 0.0f, 0.0f );
		m_world.SetGravity( gravity );

		//DebugDraw
		m_testDebugDraw.graphics = _graphics;
		m_world.SetDebugDraw( &m_testDebugDraw );

		//===========================================

		//Bodies
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set( 480, 500.0f );
		body1 = m_world.CreateBody( &bodyDef );


		bodyDef.position.Set( 520, 500.0f );
		body2 = m_world.CreateBody( &bodyDef );

		//Shapes
		b2CircleShape circleShape;
		circleShape.m_radius = 10.0f;

		//Fixtures
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &circleShape;
		fixtureDef.density = 0.01f;
		fixtureDef.friction = 0.0f;

		body1->CreateFixture( &fixtureDef );

		body2->CreateFixture( &fixtureDef );

		//Joint
		b2RevoluteJointDef revJointDef;
		revJointDef.Initialize( body1, body2, { 500.0f, 500.0f } );

		m_world.CreateJoint( &revJointDef );

		//Forces
		b2Vec2 forceApplicationPoint1 = body1->GetPosition() + b2Vec2{ 200.0f, 0.0f };
		b2Vec2 forceApplicationPoint2 = body2->GetPosition() + b2Vec2{ -200.0f, 0.0f };
		body1->ApplyLinearImpulse( m_force, forceApplicationPoint1, true );
		body2->ApplyLinearImpulse( m_force, forceApplicationPoint2, true );
		//body->ApplyLinearImpulseToCenter( m_force, true );
	}

	void update()
	{
		m_world.Step( timeStep, velocityIterations, positionIterations );
		m_debugInfo = FormatString( "Mass: %.2f Kg | X: %0.5f , Y: %0.5f", body1->GetMass(), body1->GetPosition().x, body1->GetPosition().y );

		//body1->ApplyForceToCenter( m_force, true );
	}

	void render()
	{
		m_world.DebugDraw();
	}

	b2Body* body1 = nullptr;
	b2Body* body2 = nullptr;
	b2Vec2 m_force = { 0.0f, 50.0f };

	std::string m_debugInfo;
	TestDebugDraw m_testDebugDraw;
	b2World m_world;

	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
};