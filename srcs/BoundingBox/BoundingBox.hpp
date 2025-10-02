#pragma once

#include "Algebra.hpp"
#include "Ray.hpp"

typedef struct s_splitted_box t_splitted_box;

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
    
    bool        intersect(t_ray const &ray) const;
    t_splitted_box  splitBounds(void) const;
    
    private:
    
    Point   _min;
    Point   _max;
};

typedef struct s_splitted_box {
    BoundingBox left;
    BoundingBox right;
}               t_splitted_box;
