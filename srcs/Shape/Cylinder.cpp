#include "Cylinder.hpp"

Cylinder::Cylinder() : Shape(), minimum(-INFINITY), maximum(INFINITY) {
}

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
    double  t0 = ((-b - sqrt(discriminant)) / (2 * a));
    double  t1 = ((-b + sqrt(discriminant)) / (2 * a));
    if (t0 > t1)
        swap(t0, t1);
    double  y0 = transformedRay.origin.y + t0 * transformedRay.direction.y;
    if (minimum < y0 && y0 < maximum)
        createIntersection(xs, intersection(t0, *this));
    double  y1 = transformedRay.origin.y + t1 * transformedRay.direction.y;
    if (minimum < y1 && y1 < maximum)
        createIntersection(xs, intersection(t1, *this));
        
    return (xs);
}

Vec Cylinder::normalAt(Point const &worldPoint) const {
    Point   objectPoint = this->getTransform().inverse() * worldPoint;

    return (_normalToWorld(vec(objectPoint.x, 0, objectPoint.z)));
}
