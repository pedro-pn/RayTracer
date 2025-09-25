#pragma once
#include "Shape.hpp"

class Group: public Shape {

    public:

        Group();
        ~Group() = default;

        Shape const *   operator[](int index) const;

        t_intersect intersect(t_ray const &ray) const override;
        Vec         normalAt(Point const &worldPoint) const override;

        void    addChild(shapePtr shape);

    private:

        shapeList   _children;
};
