#include "Cube.hpp"

t_intersect Cube::intersect(t_ray const &ray) const {
    t_ray          transformedRay = transformRay(ray, this->getTransform().inverse());
    t_intersect xs;

    t_cube_intersection_t  xIntersect = _checkAxis(transformedRay.origin.x, transformedRay.direction.x);
    t_cube_intersection_t  yIntersect = _checkAxis(transformedRay.origin.y, transformedRay.direction.y);
    t_cube_intersection_t  zIntersect = _checkAxis(transformedRay.origin.z, transformedRay.direction.z);

    double  tmin = max(xIntersect.tmin, max(yIntersect.tmin, zIntersect.tmin));
    double  tmax = min(xIntersect.tmax, min(yIntersect.tmax, zIntersect.tmax));
    xs.count = 0;

    if (tmin > tmax)
        return (xs);
    createIntersection(xs, intersection(tmin, *this));
    createIntersection(xs, intersection(tmax, *this));

    return (xs);
}

t_cube_intersection_t  Cube::_checkAxis(double origin, double direction) const {
    double  tminNumerator = (-1 - origin);
    double  tmaxNumerator = (1 - origin);
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
    Point   objectPoint = this->getTransform().inverse() * worldPoint;
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
