#include <precompiledphysics.h>

#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_polygon_shape.h>

namespace puma::leo
{

    struct Box2DShapes
    {
        b2CircleShape circle = {};
        b2PolygonShape polygon = {};
    };

    b2CircleShape toBox2DShape( const Circle& _shape )
    {
        b2CircleShape b2Circle;
        b2Circle.m_radius = _shape.radius;
        b2Circle.m_p = { _shape.center.x, _shape.center.y };

        return b2Circle;
    }

    b2PolygonShape toBox2DShape( const Polygon& _shape )
    {
        b2PolygonShape b2Polygon;

        std::vector<b2Vec2> b2Vectors;

        std::transform( _shape.vertices.begin(), _shape.vertices.end(), std::back_inserter( b2Vectors ), [&]( const Vec2& vec2 )
        {
            return b2Vec2( vec2.x, vec2.y );
        } );

        b2Polygon.Set( b2Vectors.data(), (s32)b2Vectors.size() );

        return b2Polygon;
    }

    template<typename Info>
    b2Shape* getShapeFromInfo( const Info& _info, Box2DShapes& _b2Shape )
    {
        b2Shape* result = nullptr;
        switch ( _info.shape.getShapeType())
        {
        case ShapeType::Circle:     
        {
            _b2Shape.circle = toBox2DShape( _info.shape.getAsCircle() ); 
            result = &_b2Shape.circle;
            break; 
        }
        case ShapeType::Polygon:  
        {
            _b2Shape.polygon = toBox2DShape( _info.shape.getAsPolygon() );
            result = &_b2Shape.polygon;
            break;
        }
        default:
        {
            assert( false ); //This shape is not supported yet
            break;
        }
        }

        return result;
    }



    b2Fixture* addBodyFixture( b2Body* _body, const BodyInfo& _bodyInfo, const CollisionMask _collisionMask )
    {
        b2FixtureDef fixDef;
        Box2DShapes b2Shapes;
        
        fixDef.shape = getShapeFromInfo( _bodyInfo, b2Shapes );
        fixDef.filter.categoryBits = 1 << _bodyInfo.collisionIndex;
        fixDef.filter.maskBits = _collisionMask;
        fixDef.density = _bodyInfo.density;
        fixDef.friction = _bodyInfo.friction;
        fixDef.restitution = _bodyInfo.restitution;

        return _body->CreateFixture( &fixDef );
    }

    b2Fixture* addTriggerFixture( b2Body* _body, const TriggerInfo& _triggerInfo, const CollisionMask _collisionMask )
    {
        b2FixtureDef fixDef;
        Box2DShapes b2Shapes;

        fixDef.shape = getShapeFromInfo( _triggerInfo, b2Shapes );
        fixDef.filter.categoryBits = 1 << _triggerInfo.collisionIndex;
        fixDef.filter.maskBits = _collisionMask;
        fixDef.density = 1.0f;
        fixDef.isSensor = true;

        return _body->CreateFixture( &fixDef );
    }
}