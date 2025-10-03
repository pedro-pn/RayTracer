#pragma once

#include "Shape.hpp"

class Triangle: public Shape {

    public:

        Triangle();
        Triangle(Point const &p1, Point const &p2, Point const &p3);
        ~Triangle() = default;

        t_intersect intersect(t_ray const &r) const override;
        Vec         normalAt(Point const &worldPoint) const override;
        BoundingBox boundsOf(void) const override;

        Point const p1(void) const;
        Point const p2(void) const;
        Point const p3(void) const;
        Point const e1(void) const;
        Point const e2(void) const;
        Vec const   normal(void) const;

    private:

        Point   _p1;
        Point   _p2;
        Point   _p3;
        Vec     _e1;
        Vec     _e2;
        Vec     _normal;

        void _initializeTriangle(Point const &p1, Point const &p2, Point const &p3);
};
