#include "Cube.hpp"

t_intersect Cube::intersect(t_ray const &ray) const {
    t_ray          transformedRay = transformRay(ray, this->getTransform().inverse());
    t_intersect xs;

    t_cube_intersection_t  xIntersect = _checkAxis(transformedRay.origin.x, transformedRay.direction.x, -1, 1);
    t_cube_intersection_t  yIntersect = _checkAxis(transformedRay.origin.y, transformedRay.direction.y, -1, 1);
    t_cube_intersection_t  zIntersect = _checkAxis(transformedRay.origin.z, transformedRay.direction.z, -1 , 1);

    double  tmin = max(xIntersect.tmin, max(yIntersect.tmin, zIntersect.tmin));
    double  tmax = min(xIntersect.tmax, min(yIntersect.tmax, zIntersect.tmax));
    xs.count = 0;

    if (tmin > tmax)
        return (xs);
    createIntersection(xs, intersection(tmin, *this));
    createIntersection(xs, intersection(tmax, *this));

    return (xs);
}

t_cube_intersection_t  Cube::_checkAxis(double origin, double direction, double min, double max) {
    double  tminNumerator = (min - origin);
    double  tmaxNumerator = (max - origin);
    t_cube_intersection_t   ts;

    if (abs(direction) >= EPSILON) {
        ts.tmin = tminNumerator / direction;
        ts.tmax = tmaxNumerator / direction;
    } else {
        ts.tmin = tminNumerator * INFINITY;
        ts.tmax = tmaxNumerator * INFINITY;
    }

    if (ts.tmin > ts.tmax)
        swap<double>(ts.tmin, ts.tmax);
    
    return (ts);
}

Vec Cube::normalAt(Point const &worldPoint) const {
    Point   objectPoint = this->_worldToObject(worldPoint);
    Vec     normal;

    double  maxc = max(abs(objectPoint.x), max(abs(objectPoint.y), abs(objectPoint.z)));
    if (areEqual(maxc, abs(objectPoint.x)))
        normal = vec(objectPoint.x, 0, 0);
    else if (areEqual(maxc, abs(objectPoint.y)))
        normal = vec(0, objectPoint.y, 0);
    else if (areEqual(maxc, abs(objectPoint.z)))
        normal = vec(0, 0, objectPoint.z);

    return (_normalToWorld(normal));
}

BoundingBox Cube::boundsOf(void) const {
    return (BoundingBox(point(-1, -1, -1), point(1, 1, 1)));
}
