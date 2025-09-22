#pragma once

#include "Shape.hpp"

typedef struct s_cube_intersection_t {
    double  tmin;
    double  tmax;
}               t_cube_intersection_t;

class Cube: public Shape {

    public:

        Cube() = default;
        ~Cube() = default;

        t_intersect intersect(t_ray const &ray) const override;
        Vec normalAt(Point const &worldPoint) const override;

    private:

        t_cube_intersection_t   _checkAxis(double origin, double direction) const;

};
