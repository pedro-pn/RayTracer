#pragma once

#include "Algebra.hpp"
#include "Sphere.hpp"
#include <vector>
#include <optional>

// RAY

typedef struct s_ray {
    Point   origin;
    Vec     direction;

    s_ray(Point const &origin, Vec const &direction) : origin(origin), direction(direction) {}
}           t_ray;

typedef struct s_intersection {
    double  t;
    Sphere  object;

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

    s_intersect operator+=(s_intersect const &rhs) {
        this->count += rhs.count;
        this->intersections.insert(this->intersections.end(), rhs.intersections.begin(), rhs.intersections.end());
        return (*this);
    }
}               t_intersect;

// RAYS

t_ray           ray(Point const &origin, Vec const &direction);
Point           position(t_ray const &ray, double t);
t_intersect     intersect(Sphere const &s, t_ray const &r);
t_intersection  intersection(double t, Sphere const &s);
optional<t_intersection>    hit(t_intersect &xs);
t_ray           transformRay(t_ray const &r, Matrix const &transform);