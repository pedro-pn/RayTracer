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

    if (discriminant < 0) {
        xs.count = 0;
        return (xs);
    }
    xs.count = 2;
    double t1 = ((-b - sqrt(discriminant))/(2 * a));
    double t2 = ((-b + sqrt(discriminant))/(2 * a));
    xs.intersections.push_back(intersection(t1, *this));
    xs.intersections.push_back(intersection(t2, *this));
    return (xs);
}

Vec Sphere::normalAt(Point const &worldPoint) const {
    Point   objectPoint = this->getTransform().inverse() * worldPoint;
    Vec     objectNormal = objectPoint - this->getOrigin();
    Vec     worldNormal = this->getTransform().inverse().transpose() * objectNormal;
    worldNormal.w = 0;
    return (worldNormal.normalize());
}
