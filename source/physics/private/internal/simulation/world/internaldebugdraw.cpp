#include <precompiledphysics.h>

#include "internaldebugdraw.h"

namespace puma::physics
{

    InternalDebugDraw::InternalDebugDraw( InternalDebugDraw&& _other ) noexcept
    {
        debugDraw = std::move( _other.debugDraw );
    }

    void InternalDebugDraw::DrawPolygon( const b2Vec2* vertices, int32 vertexCount, const b2Color& color )
    {
        std::vector<Vec2> castedVertices( vertexCount );

        for ( int index = 0; index < vertexCount; ++index )
        {
            castedVertices[index].x = vertices[index].x;
            castedVertices[index].y = vertices[index].y;
        }

        debugDraw->renderPolygon( std::move( castedVertices ), { color.r, color.g, color.b, color.a } );
    }

    void InternalDebugDraw::DrawSolidPolygon( const b2Vec2* vertices, int32 vertexCount, const b2Color& color )
    {
        std::vector<Vec2> castedVertices( vertexCount );

        for ( int index = 0; index < vertexCount; ++index )
        {
            castedVertices[index].x = vertices[index].x;
            castedVertices[index].y = vertices[index].y;
        }

        debugDraw->renderSolidPolygon( std::move( castedVertices ), { color.r, color.g, color.b, color.a } );
    }

    void InternalDebugDraw::DrawCircle( const b2Vec2& center, float radius, const b2Color& color )
    {
        debugDraw->renderCircle( { center.x, center.y }, radius, { color.r, color.g, color.b, color.a } );
    }

    void InternalDebugDraw::DrawSolidCircle( const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color )
    {
        debugDraw->renderSolidCircle( { center.x, center.y }, radius, { color.r, color.g, color.b, color.a } );
    }

    void InternalDebugDraw::DrawSegment( const b2Vec2& p1, const b2Vec2& p2, const b2Color& color )
    {
        debugDraw->renderSegment( { p1.x, p1.y }, { p1.x, p1.y }, { color.r, color.g, color.b, color.a } );
    }

    void InternalDebugDraw::DrawTransform( const b2Transform& xf )
    {

    }

    void InternalDebugDraw::DrawPoint( const b2Vec2& p, float size, const b2Color& color )
    {
        debugDraw->renderSolidCircle( { p.x, p.y }, size, { color.r, color.g, color.b, color.a } );
    }
}