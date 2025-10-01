#include "Plane.hpp"

t_intersect         Plane::intersect(t_ray const &r) const {
    t_intersect     xs;
    t_ray           transformedRay = transformRay(r, this->getTransform().inverse());
    double          t;

    xs.count = 0;
    if (abs(transformedRay.direction.y) < EPSILON)
        return (xs);
    t = -transformedRay.origin.y / transformedRay.direction.y;
    createIntersection(xs, intersection(t, *this));

    return (xs);
}

Vec Plane::normalAt(Point const &worldPoint) const {
    (void)worldPoint;
    return (_normalToWorld(vec(0, 1, 0)));
}

BoundingBox Plane::boundsOf(void) const {
    return (BoundingBox(point(-INFINITY, 0, -INFINITY), point(INFINITY, 0, INFINITY)));
}