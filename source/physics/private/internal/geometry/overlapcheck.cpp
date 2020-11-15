#include <precompiledphysics.h>

#include <physics/geometry/overlapcheck.h>

#include <physics/geometry/shapes.h>

#include <box2d/b2_collision.h>

namespace puma::physics
{

    namespace
    {
        //bool isPointInBox( Vec2 _point, Vec2 _upperLeft, Vec2 _lowerRight )
        //{
        //    return  ((_point.x >= _upperLeft.x) &&
        //            (_point.x <= _lowerRight.x) &&
        //            (_point.y >= _upperLeft.y) &&
        //            (_point.y <= _lowerRight.y));
        //}

        //bool arePointsClose( Vec2 _point1, Vec2 _point2, float _collisionDistance )
        //{
        //    Vec2 difference = _point1 - _point2;
        //    float length = difference.squaredLength();

        //    return length < (_collisionDistance * _collisionDistance);
        //}

        //bool isAbove( Vec2 _point, Vec2 _upperBound )
        //{
        //    return _point.y > _upperBound.y;
        //}

        //bool isBelow( Vec2 _point, Vec2 _lowerBound )
        //{
        //    return _point.y < _lowerBound.y;
        //}

        //bool isAtLeft( Vec2 _point, Vec2 _lowerBound )
        //{
        //    return _point.x < _lowerBound.x;
        //}

        //bool isAtRight( Vec2 _point, Vec2 _upperBound )
        //{
        //    return _point.x > _upperBound.x;
        //}
    }

    template<>
    bool areShapesOverLapping( Rectangle _rect1, Rectangle _rect2 )
    {
        b2AABB bb1 = { {_rect1.lowerBoundary.x, _rect1.lowerBoundary.y}, {_rect1.upperBoundary.x, _rect1.upperBoundary.y} };
        b2AABB bb2 = { {_rect2.lowerBoundary.x, _rect2.lowerBoundary.y}, {_rect2.upperBoundary.x, _rect2.upperBoundary.y} };

        bool result = b2TestOverlap( bb1, bb2 );
        return result;
    }

    /*template<>
    bool areShapesOverLapping( Circle _circle1, Circle _circle2 )
    {
        float collisionDistance = (_circle1.radius + _circle2.radius);

        return arePointsClose( _circle1.center, _circle2.center, collisionDistance );
    }

    template<>
    bool areShapesOverLapping( Circle _circle, Rectangle _rect )
    {
        physics::Vec2 center1 = _circle.center;
        float radius1 = _circle.radius;

        physics::Vec2 upperBound = _rect.upperBoundary;
        physics::Vec2 lowerBound = _rect.lowerBoundary;

        bool collided = false;

        if ( isAbove( center1, upperBound ) )
        {
            if ( isAtLeft( center1, lowerBound ) )
            {
                collided = arePointsClose( { lowerBound.x, upperBound.y }, center1, radius1 );
            }
            else if ( isAtRight( center1, upperBound ) )
            {
                collided = arePointsClose( upperBound, center1, radius1 );
            }
            else
            {
                collided = arePointsClose( { center1.x, upperBound.y }, center1, radius1 );
            }
        }
        else if ( isBelow( center1, lowerBound ) )
        {
            if ( isAtLeft( center1, lowerBound ) )
            {
                collided = arePointsClose( lowerBound, center1, radius1 );
            }
            else if ( isAtRight( center1, upperBound ) )
            {
                collided = arePointsClose( { upperBound.x, lowerBound.y }, center1, radius1 );
            }
            else
            {
                collided = arePointsClose( { center1.x, lowerBound.y }, center1, radius1 );
            }
        }
        else
        {
            if ( isAtLeft( center1, lowerBound ) )
            {
                collided = arePointsClose( { lowerBound.x, center1.y }, center1, radius1 );
            }
            else if ( isAtRight( center1, upperBound ) )
            {
                collided = arePointsClose( { upperBound.x, center1.y }, center1, radius1 );
            }
        }

        return collided;
    }

    template<>
    bool areShapesOverLapping( Rectangle _rect, Circle _circle )
    {
        return areShapesOverLapping( _circle, _rect );
    }*/
}