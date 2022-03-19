#include <precompiledphysics.h>

#include <physics/geometry/overlapcheck.h>

#include <utils/graphics/dimensions.h>

#include <box2d/b2_collision.h>

namespace puma::leo
{
    template<>
    bool areShapesOverLapping( Rectangle _rect1, Rectangle _rect2 )
    {
        b2AABB bb1 = { {_rect1.lowerBoundary.x, _rect1.lowerBoundary.y}, {_rect1.upperBoundary.x, _rect1.upperBoundary.y} };
        b2AABB bb2 = { {_rect2.lowerBoundary.x, _rect2.lowerBoundary.y}, {_rect2.upperBoundary.x, _rect2.upperBoundary.y} };

        bool result = b2TestOverlap( bb1, bb2 );
        return result;
    }
}