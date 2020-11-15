#pragma once

#include <physics/geometry/vec2.h>

namespace puma::physics
{
    struct RGBA
    {
        float r = 1.0f;
        float g = 1.0f;
        float b = 1.0f;
        float a = 1.0f;
    };

    class DebugDraw
    {
    public:
        virtual ~DebugDraw() {}

        virtual void renderPolygon( const std::vector<Vec2>&& _vertices, const RGBA& _color ) = 0;
        virtual void renderSolidPolygon( const std::vector<Vec2>&& _vertices, const RGBA& _color ) = 0;
        virtual void renderCircle( const Vec2&& _center, float _radius, const RGBA& _color ) = 0;
        virtual void renderSolidCircle( const Vec2&& _center, float _radius, const RGBA& _color ) = 0;
        virtual void renderSegment( const Vec2&& _point1, const Vec2& _point2, const RGBA& _color ) = 0;
    };
}