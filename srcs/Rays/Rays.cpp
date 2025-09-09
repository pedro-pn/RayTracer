#include "RayTracer.hpp"

t_ray   ray(Point const &origin, Vec const &direction) {
    return ((t_ray){origin, direction});
}

Point   position(t_ray  const &r, double t) {
    return (r.origin + r.direction * t);
}

t_intersection  intersection(double t, Shape const &s) {
    t_intersection  inter;

    inter.shape = &s;
    inter.t = t;

    return (inter);
}

optional<t_intersection>    hit(t_intersect &xs) {
    if (xs.count == 0)
        return (nullopt);

    sort(xs.intersections.begin(), xs.intersections.end());
    for (auto it = xs.intersections.begin();  it != xs.intersections.end(); it++ ) {
        if ((*it).t >= EPSILON)
            return (*it);
    }

    return (nullopt);
}

t_ray   transformRay(t_ray const &r, Matrix const &transform) {
    Point   p;
    Vec     v;

    p = transform * r.origin;
    v = transform * r.direction;
    return (ray(p, v));
}
