#include "RayTracer.hpp"
#include <list>

static void getRefractiveIndex(t_computations &comps, t_intersection const &inter, t_intersect &xs) {
    list<Shape const *> container;

    for (auto it = xs.intersections.begin(); it != xs.intersections.end(); it++) {
        if (*it == inter) {
            if (container.empty())
                comps.n1 = 1.0;
            else
                comps.n1 = container.back()->getMaterial().refractiveIndex;
        }
        if (std::find(container.begin(), container.end(), it->shape) != container.end())
            container.remove(it->shape);
        else
            container.push_back(it->shape);
        if (*it == inter) {
            if (container.empty())
                comps.n2 = 1.0;
            else
                comps.n2 = container.back()->getMaterial().refractiveIndex;
        }
    }
}

t_computations  prepareComputations(t_intersection const &inter, t_ray const &ray, t_intersect &xs) {
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
    comps.underPoint = comps.point - (comps.normalv * EPSILON);
    getRefractiveIndex(comps, inter, xs);
    return (comps);
} 

Color   shadeHit(World const &world, t_computations const &comps, int remaining) {
    Color   surfaceColor = lighting(*comps.shape, world.getLight(), comps.overPoint, comps.eyev, comps.normalv, world.isShadowed(comps.overPoint));
    Color   reflectColor = reflectedColor(world, comps, remaining);
    Color   refractColor = refractedColor(world, comps, remaining);
    t_material  material = comps.shape->getMaterial();

    if (material.reflective > 0 && material.transparency > 0) {
        double reflectance = schlick(comps);
        return (surfaceColor + reflectColor * reflectance + refractColor * (1 - reflectance));
    }

    return (surfaceColor + reflectColor + refractColor);
}

Color   colorAt(World const &world, t_ray const &ray, int remaining) {
    t_intersect     intersects = world.intersectWorld(ray);
    auto            hits = hit(intersects);
    t_computations  comps;

    if (hits == nullopt)
        return (ColorUtils::black());
    comps = prepareComputations(*hits, ray, intersects);

    return (shadeHit(world, comps, remaining));
}

Color   reflectedColor(World const &world, t_computations const &comps, int remaining) {
    if (comps.shape->getMaterial().reflective == 0 || remaining <= 0)
        return (ColorUtils::black());
    
    t_ray   reflectedRay = ray(comps.overPoint, comps.reflectv);
    Color   resultColor = colorAt(world, reflectedRay, remaining - 1);

    return (resultColor * comps.shape->getMaterial().reflective);
}

Color   refractedColor(World const &world, t_computations const &comps, int remaining) {
    if (comps.shape->getMaterial().transparency == 0 || remaining == 0)
        return (color(0, 0, 0));
    
    double  nRatio = comps.n1 / comps.n2;
    double  cosI = dot(comps.eyev, comps.normalv);
    double  sin2t = pow(nRatio, 2) * (1 - pow(cosI, 2));
    double  cosT = sqrt(1.0 - sin2t);

    Vec     direction = (comps.normalv * (nRatio * cosI - cosT)) - (comps.eyev * nRatio);
    t_ray   refractedRay = ray(comps.underPoint, direction);
    if (sin2t > 1)
        return (color(0, 0, 0));

    return (colorAt(world, refractedRay, remaining - 1) * comps.shape->getMaterial().transparency);
}

double  schlick(t_computations const &comps) {
    double  cosine = dot(comps.eyev, comps.normalv);

    if (comps.n1 > comps.n2) {
        double n = comps.n1 / comps.n2;
        double sin2t = pow(n, 2) * (1.0 - pow(cosine, 2));
        if (sin2t > 1.0)
            return (1.0);
        double cosT = sqrt(1.0 - sin2t);
        cosine = cosT;
    }
    double result = pow(((comps.n1 - comps.n2) / (comps.n1 + comps.n2)), 2);
    return (result + (1 - result) * pow((1 - cosine), 5));
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
