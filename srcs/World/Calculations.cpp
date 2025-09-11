#include "RayTracer.hpp"

t_computations  prepareComputations(t_intersection const &inter, t_ray const &ray) {
    t_computations comps;

    comps.t = inter.t;
    comps.shape = inter.shape;
    comps.point = position(ray, comps.t);
    comps.normalv = comps.shape->normalAt(comps.point);
    comps.eyev = -ray.direction;
    
    if (dot(comps.normalv, comps.eyev) < 0) {
        comps.inside = true;
        comps.normalv = -comps.normalv;
    } else {
        comps.inside = false;
    }
    comps.reflectv = reflect(ray.direction, comps.normalv);
    comps.overPoint = comps.point + (comps.normalv * EPSILON);
    return (comps);
} 

Color   shadeHit(World const &world, t_computations const &comps, int remaining) {
    Color   surfaceColor = lighting(*comps.shape, world.getLight(), comps.overPoint, comps.eyev, comps.normalv, world.isShadowed(comps.overPoint));
    Color   reflectColor = reflectedColor(world, comps, remaining);
    return (surfaceColor + reflectColor);
}

Color   colorAt(World const &world, t_ray const &ray, int remaining) {
    t_intersect     intersects = world.intersectWorld(ray);
    auto            hits = hit(intersects);
    t_computations  comps;

    if (hits == nullopt)
        return (ColorUtils::black());
    comps = prepareComputations(*hits, ray);

    return (shadeHit(world, comps, remaining));
}

Color   reflectedColor(World const &world, t_computations const &comps, int remaining) {
    if (comps.shape->getMaterial().reflective == 0 || remaining <= 0)
        return (ColorUtils::black());
    
    t_ray   reflectedRay = ray(comps.overPoint, comps.reflectv);
    Color   resultColor = colorAt(world, reflectedRay, remaining - 1);

    return (resultColor * comps.shape->getMaterial().reflective);
}

Matrix  viewTransformation(Point const &from, Point const &to, Vec const &up) {
    Vec forward = (to - from).normalize();
    Vec left = cross(forward, up.normalize());
    Vec trueUp = cross(left, forward);
    Matrix  orientation((t_setMatrix){
        left.x, left.y, left.z, 0,
        trueUp.x, trueUp.y, trueUp.z, 0,
        -forward.x, -forward.y, -forward.z, 0,
        0, 0, 0, 1
    });
    return (orientation * translation(-from.x, -from.y, -from.z));
}
