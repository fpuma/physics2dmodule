#pragma once

#include <physics/geometry/vec2.h>

namespace puma::physics
{
    enum class ShapeType
    {
        Circle,
        Rectangle,
    };

    struct Rectangle
    {
        Vec2 upperBoundary;
        Vec2 lowerBoundary;
    };

    struct Circle
    {
        physics::Vec2 center;
        float radius = 1.0f;
    };

    union Shape
    {
        Shape() {}
        Circle circle = {};
        Rectangle rectangle;
    };
}