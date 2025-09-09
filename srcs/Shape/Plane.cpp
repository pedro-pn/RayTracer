#include "Plane.hpp"

t_intersect         Plane::intersect(t_ray const &r) const {
    t_intersect     xs;
    t_ray           transformedRay = transformRay(r, this->getTransform().inverse());
    double          t;

    xs.count = 0;
    if (abs(transformedRay.direction.y) < EPSILON)
        return (xs);
    xs.count = 1;
    t = -transformedRay.origin.y / transformedRay.direction.y;
    xs.intersections.push_back(intersection(t, *this));

    return (xs);
}

Vec Plane::normalAt(Point const &worldPoint) const {
    (void)worldPoint;
    return (vec(0, 1, 0));
}
