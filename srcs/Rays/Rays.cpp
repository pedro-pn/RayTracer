#include <RayTracer.hpp>

t_ray   ray(Point const &origin, Vec const &direction) {
    return ((t_ray){origin, direction});
}

Point   position(t_ray  const &r, double t) {
    return (r.origin + r.direction * t);
}

t_intersection  intersection(double t, Sphere const *s) {
    t_intersection  inter;

    inter.object = s;
    inter.t = t;

    return (inter);
}

t_intersect intersect(Sphere const *s, t_ray const &r) {
    t_ray           transformedRay = transformRay(r, s->getTransform().inverse());
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
    xs.intersections.push_back(intersection(t1, s));
    xs.intersections.push_back(intersection(t2, s));
    return (xs);
}

optional<t_intersection>    hit(t_intersect &xs) {
    if (xs.count == 0)
        return (nullopt);

    sort(xs.intersections.begin(), xs.intersections.end());
    for (auto it = xs.intersections.begin();  it != xs.intersections.end(); it++ ) {
        if ((*it).t >= 0)
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
