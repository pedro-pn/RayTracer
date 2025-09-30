#pragma once

#include "Algebra.hpp"

class BoundingBox {

    public:

        BoundingBox();
        BoundingBox(Point const &min, Point const &max);
        ~BoundingBox() = default;

        Point const &getMin(void) const;
        Point const &getMax(void) const;

        void        addPoint(Point const &point);

    private:

        Point   _min;
        Point   _max;
};
