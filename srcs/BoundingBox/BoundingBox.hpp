#pragma once

#include "Algebra.hpp"

class BoundingBox {

    public:

        BoundingBox();
        BoundingBox(Point const &min, Point const &max);
        ~BoundingBox() = default;

        BoundingBox operator+(BoundingBox const &rhs) const;
        BoundingBox operator+(Point const &rhs) const;

        BoundingBox transform(Matrix const &transform) const;

        Point const &getMin(void) const;
        Point const &getMax(void) const;

        void        addPoint(Point const &point);
        void        addBox(BoundingBox const &box);
        bool        containsPoint(Point const &point) const;
        bool        containsBox(BoundingBox const &box) const;

    private:

        Point   _min;
        Point   _max;
};
