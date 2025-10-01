#pragma once
#include "Cylinder.hpp"

class Cone: public Cylinder {

    public:

        Cone();
        ~Cone() = default;

    t_intersect intersect(t_ray const &ray) const override;
    Vec         normalAt(Point const &worldPoint) const override;
    BoundingBox boundsOf(void) const override;

    private:

        void    _intersectWalls(t_ray const &ray, t_intersect &xs) const;
        void    _intersectCaps(t_ray const &ray, t_intersect &xs) const;
        bool    _checkCap(t_ray const &ray, double t, double y) const;

};
