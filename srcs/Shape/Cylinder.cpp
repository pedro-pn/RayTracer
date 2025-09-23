#include "Cylinder.hpp"

t_intersect Cylinder::intersect(t_ray const &ray) const {
    t_ray   transformedRay = transformRay(ray, this->getTransform().inverse());
    t_intersect xs;
    double  a = pow(transformedRay.direction.x, 2) + pow(transformedRay.direction.z, 2);

    xs.count = 0;
    if (areEqual(a, 0))
        return (xs);
    double  b = 2 * transformedRay.origin.x * transformedRay.direction.x + 2 * transformedRay.origin.z * transformedRay.direction.z;
    double  c = pow(transformedRay.origin.x, 2) + pow(transformedRay.origin.z, 2) - 1;
    double  discriminant = pow(b, 2) - 4 * a * c;

    if (discriminant < 0)
        return (xs);
    xs.count = 2;
    double  t0 = ((-b - sqrt(discriminant)) / (2 * a));
    double  t1 = ((-b + sqrt(discriminant)) / (2 * a));
    xs.intersections.push_back(intersection(t0, *this));
    xs.intersections.push_back(intersection(t1, *this));

    return (xs);
}

Vec Cylinder::normalAt(Point const &worldPoint) const {
    Point   objectPoint = this->getTransform().inverse() * worldPoint;

    return (_normalToWorld(vec(objectPoint.x, 0, objectPoint.z)));
}
