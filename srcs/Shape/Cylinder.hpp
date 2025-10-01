#pragma once
#include "Shape.hpp"

class Cylinder: public Shape {

    public:

        Cylinder();
        ~Cylinder() = default;

        t_intersect intersect(t_ray const &ray) const override;
        Vec         normalAt(Point const &worldPoint) const override;
        BoundingBox boundsOf(void) const override;

        bool      isClosed() const;
        double    getMinimum(void) const;
        double    getMaximum(void) const;
        void            setMinimum(double n);
        void            setMaximum(double n);


        void         closed(void);
        void         opened(void);

        
    protected:
    
        bool    _isClosed;
        double  _minimum;
        double  _maximum;

    private:
    
        bool    _checkCap(t_ray const &ray, double t) const;
        void    _intersectCaps(t_ray const &ray, t_intersect &xs) const;
        void    _intersectWalls(t_ray const &ray, t_intersect &xs) const;
};
