#pragma once

#include "Shape.hpp"

class Plane: public Shape {

    public:
        
        Plane() = default;
        ~Plane() = default;

        t_intersect         intersect(t_ray const &r) const override;
        Vec         normalAt(Point const &worldPoint) const override;
};
