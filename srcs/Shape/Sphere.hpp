#pragma once

#include "Shape.hpp"

class Sphere: public Shape {

    public:

        Sphere();
        ~Sphere() override;

        t_intersect intersect(t_ray const &r) const override;
        Vec         normalAt(Point const &worldPoint) const override;

    private:

        Point     _origin;
};
