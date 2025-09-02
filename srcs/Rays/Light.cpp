#include "RayTracer.hpp"

Vec normalAt(Sphere const *object, Point const &worldPoint) {
    Point   objectPoint = object->getTransform().inverse() * worldPoint;
    Vec     objectNormal = objectPoint - object->getOrigin();
    Vec     worldNormal = object->getTransform().inverse().transpose() * objectNormal;
    worldNormal.w = 0;
    return (worldNormal.normalize());
}

Vec reflect(Vec const &incomingRay, Vec const &normal) {
    return (incomingRay - normal * 2 * dot(incomingRay, normal));
}

t_light pointLight(Point const &position, Color const &intensity) {
    return (t_light(position, intensity));
}
