#pragma once

#include "Algebra.hpp"
#include <vector>
#include <optional>

// RAY

typedef struct s_ray {
    Point   origin;
    Vec     direction;

    s_ray() : origin(point(0, 0, 0)), direction(vec(0, 0, 0)) {}
    s_ray(Point const &origin, Vec const &direction) : origin(origin), direction(direction) {}
}           t_ray;

// RAYS

t_ray           ray(Point const &origin, Vec const &direction);
Point           position(t_ray const &ray, double t);
t_ray           transformRay(t_ray const &r, Matrix const &transform);
