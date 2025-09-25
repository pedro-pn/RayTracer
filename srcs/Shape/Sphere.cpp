#include "Sphere.hpp"

Sphere::Sphere(): _origin(point(0, 0, 0)) {
}

Sphere::~Sphere() {
}

t_intersect Sphere::intersect(t_ray const &r) const {
    t_ray           transformedRay = transformRay(r, this->getTransform().inverse());
    Point           sphereToRay = transformedRay.origin - point(0, 0, 0);
    t_intersect     xs;

    double a = dot(transformedRay.direction, transformedRay.direction);
    double b = 2 * dot(transformedRay.direction, sphereToRay);
    double c = dot(sphereToRay, sphereToRay) - 1;
    double discriminant = (b * b) - 4 * a * c;
    xs.count = 0;

    if (discriminant < 0)
        return (xs);
    double t1 = ((-b - sqrt(discriminant))/(2 * a));
    double t2 = ((-b + sqrt(discriminant))/(2 * a));
    createIntersection(xs, intersection(t1, *this));
    createIntersection(xs, intersection(t2, *this));
    return (xs);
}

Vec Sphere::normalAt(Point const &worldPoint) const {
    Point   objectPoint = this->_worldToObject(worldPoint);
    Vec     objectNormal = objectPoint - this->_origin;
    return (_normalToWorld(objectNormal));
}

// MISC

Sphere  glassSphere(void) {
    Sphere s;
    s.getMaterial().transparency = 1.0;
    s.getMaterial().refractiveIndex = 1.5;
    return (s);
}
