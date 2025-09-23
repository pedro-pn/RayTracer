#pragma once
#include "Shape.hpp"

class Cylinder: public Shape {

    public:

        Cylinder();
        ~Cylinder() = default;

        t_intersect intersect(t_ray const &ray) const override;
        Vec         normalAt(Point const &worldPoint) const override;

        double  minimum;
        double  maximum;

};
