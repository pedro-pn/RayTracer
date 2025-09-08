#include "Plane.hpp"

t_intersect         Plane::intersect(t_ray const &r) const {
    t_intersect     xs;
    t_ray           transformedRay = transformRay(r, this->getTransform().inverse());

    xs.count = 0;
    if (abs(transformedRay.direction.y) < EPSILON)
        return (xs);
    xs.count = 1;
    xs.intersections.push_back(intersection(1, *this));

    return (xs);
}

Vec Plane::normalAt(Point const &point) const {
    (void)point;
    return (vec(0, 1, 0));
}
