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
    comps.overPoint = comps.point + (comps.normalv * EPSILON);
    return (comps);
} 

Color   shadeHit(World const &world, t_computations const &comps) {
    return (lighting(*comps.shape, world.getLight(), comps.overPoint, comps.eyev, comps.normalv, world.isShadowed(comps.overPoint)));
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
