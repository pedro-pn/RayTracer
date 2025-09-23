#pragma once

#include "Algebra.hpp"
#include <vector>
#include <optional>

class Shape;

typedef struct s_intersection {
    double  t;
    Shape const *shape;

    bool    operator==(struct s_intersection const &rhs) const {
        return (this->t == rhs.t && this->shape == rhs.shape);
    }
    bool    operator<(struct s_intersection const &rhs) const {
        return (this->t < rhs.t);
    }
    bool    operator>(struct s_intersection const &rhs) const {
        return (this->t > rhs.t);
    }
}               t_intersection;

typedef struct s_intersect {
    int                     count;
    vector<t_intersection>  intersections;

    s_intersect operator+=(s_intersect const &rhs) {
        this->count += rhs.count;
        this->intersections.insert(this->intersections.end(), rhs.intersections.begin(), rhs.intersections.end());
        return (*this);
    }
}               t_intersect;

optional<t_intersection>    hit(t_intersect &xs);
t_intersection              intersection(double t, Shape const &s);
void                        createIntersection(t_intersect &xs, t_intersection &&inter);
void                        createIntersection(t_intersect &xs, t_intersection &inter);
