#ifndef RAYTRACER_HPP
# define RAYTRACER_HPP

# pragma once
# include "Algebra.hpp"
# include "Matrix.hpp"
# include "Tuple.hpp"
# include "ColorUtils.hpp"
# include "Canvas.hpp"
# include "Material.hpp"
# include "Sphere.hpp"
# include <vector>
# include <memory>
# include <optional>
# include <algorithm>

// RAY

typedef struct s_ray {
    Point   origin;
    Vec     direction;

    s_ray(Point const &origin, Vec const &direction) : origin(origin), direction(direction) {}
}           t_ray;

typedef struct s_intersection {
    double  t;
    Sphere const *object;

    bool    operator==(struct s_intersection const &rhs) const {
        return (this->t == rhs.t && this->object == rhs.object);
    }
    bool    operator<(struct s_intersection const &rhs) const {
        return (this->t < rhs.t);
    }
    bool    operator>(struct s_intersection const &rhs) const {
        return (this->t > rhs.t);
    }
}               t_intersection;

typedef struct s_intersect {
    int                     count;
    vector<t_intersection>  intersections;
}               t_intersect;

// RAYS

t_ray           ray(Point const &origin, Vec const &direction);
Point           position(t_ray const &ray, double t);
t_intersect     intersect(Sphere const *s, t_ray const &r);
t_intersection  intersection(double t, Sphere const *s);
optional<t_intersection>    hit(t_intersect &xs);
t_ray           transformRay(t_ray const &r, Matrix const &transform);

// LIGHT

typedef struct s_light {
    Point   position;
    Color   intensity;

    s_light(Point const &position, Color const &intensity) : position(position), intensity(intensity) {}
}           t_light;

Vec             normalAt(Sphere const *object, Point const &worldPoint);
Vec             reflect(Vec const &incomingRay, Vec const &normal);
t_light         pointLight(Point const &position, Color const &intensity);
Color           lighting(t_material const &material, t_light const &light, Point const &point, Vec const &eyev, Vec const &normalv);

// DEMOS

void    clockDemo(void);
void    sphereDemo(void);

#endif
