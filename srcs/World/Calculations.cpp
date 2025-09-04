#include "RayTracer.hpp"

t_computations  prepareComputations(t_intersection const &inter, t_ray const &ray) {
    t_computations comps;

    comps.t = inter.t;
    comps.object = inter.object;
    comps.point = position(ray, comps.t);
    comps.eyev = -ray.direction;
    comps.normalv = normalAt(comps.object, comps.point);

    if (dot(comps.normalv, comps.eyev) < 0) {
        comps.inside = true;
        comps.normalv = -comps.normalv;
    } else {
        comps.inside = false;
    }
    return (comps);
}

Color   shadeHit(World const &world, t_computations const &comps) {
    return (lighting(comps.object.getMaterial(), world.getLight(), comps.point, comps.eyev, comps.normalv));
}

Color   colorAt(World const &world, t_ray const &ray) {
    t_intersect     intersects = world.intersectWorld(ray);
    auto            hits = hit(intersects);
    t_computations  comps;

    if (hits == nullopt)
        return (ColorUtils::black());
    comps = prepareComputations(*hits, ray);

    return (shadeHit(world, comps));
}
