#pragma once

#include <leo/debug/debugdraw.h>

#include <box2d/b2_draw.h>

namespace puma::leo
{
    class InternalDebugDraw : public b2Draw, public NonCopyable
    {
    public:

        InternalDebugDraw() {}
        InternalDebugDraw( InternalDebugDraw&& _other ) noexcept;

        void DrawPolygon( const b2Vec2* vertices, int32 vertexCount, const b2Color& color ) override;
        void DrawSolidPolygon( const b2Vec2* vertices, int32 vertexCount, const b2Color& color ) override;
        void DrawCircle( const b2Vec2& center, float radius, const b2Color& color ) override;
        void DrawSolidCircle( const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color ) override;
        void DrawSegment( const b2Vec2& p1, const b2Vec2& p2, const b2Color& color ) override;
        void DrawTransform( const b2Transform& xf ) override;
        void DrawPoint( const b2Vec2& p, float size, const b2Color& color ) override;

        std::unique_ptr<puma::leo::DebugDraw> debugDraw = nullptr;
    };
}