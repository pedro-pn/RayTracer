#include "Cylinder.hpp"

Cylinder::Cylinder() : Shape(), _isClosed(false), _minimum(-INFINITY), _maximum(INFINITY) {
}

bool    Cylinder::_checkCap(t_ray const &ray, double t) const {
    double x = ray.origin.x + t * ray.direction.x;
    double z = ray.origin.z + t * ray.direction.z;

    return ((pow(x, 2) + pow(z, 2)) <= 1);
}

void    Cylinder::_intersectCaps(t_ray const &ray, t_intersect &xs) const {
    if (_isClosed == false || areEqual(ray.direction.y, 0))
        return ;
    
    double  t = (_minimum - ray.origin.y) / ray.direction.y;
    if (_checkCap(ray, t))
        createIntersection(xs, intersection(t, *this));

    t = (_maximum - ray.origin.y) / ray.direction.y;
    if (_checkCap(ray, t))
        createIntersection(xs, intersection(t, *this));
}

void    Cylinder::_intersectWalls(t_ray const &ray, t_intersect &xs) const {
    double  a = pow(ray.direction.x, 2) + pow(ray.direction.z, 2);

    if (areEqual(a, 0))
        return ;
    double  b = 2 * ray.origin.x * ray.direction.x + 2 * ray.origin.z * ray.direction.z;
    double  c = pow(ray.origin.x, 2) + pow(ray.origin.z, 2) - 1;
    double  discriminant = pow(b, 2) - 4 * a * c;

    if (discriminant < 0)
        return ;
    double  t0 = ((-b - sqrt(discriminant)) / (2 * a));
    double  t1 = ((-b + sqrt(discriminant)) / (2 * a));
    if (t0 > t1)
        swap(t0, t1);
    double  y0 = ray.origin.y + t0 * ray.direction.y;
    if (_minimum < y0 && y0 < _maximum)
        createIntersection(xs, intersection(t0, *this));
    double  y1 = ray.origin.y + t1 * ray.direction.y;
    if (_minimum < y1 && y1 < _maximum)
        createIntersection(xs, intersection(t1, *this));
}

t_intersect Cylinder::intersect(t_ray const &ray) const {
    t_ray   transformedRay = transformRay(ray, this->getTransform().inverse());
    t_intersect xs;
    
    xs.count = 0;
    _intersectWalls(transformedRay, xs);
    _intersectCaps(transformedRay, xs);
        
    return (xs);
}

Vec Cylinder::normalAt(Point const &worldPoint) const {
    Point   objectPoint = this->getTransform().inverse() * worldPoint;
    double  dist = pow(objectPoint.x, 2) + pow(objectPoint.z, 2);

    if (dist < 1 && objectPoint.y >= (_maximum - EPSILON))
        return (_normalToWorld(vec(0, 1, 0)));
    else if (dist < 1 && objectPoint.y <= (_minimum + EPSILON))
        return (_normalToWorld(vec(0, -1, 0)));

    return (_normalToWorld(vec(objectPoint.x, 0, objectPoint.z)));
}

bool     Cylinder::isClosed(void) const {
    return (_isClosed);
}

double   Cylinder::getMinimum(void) const { 
    return (_minimum);
}

double   Cylinder::getMaximum(void) const { 
    return (_maximum);
}

void            Cylinder::setMinimum(double n) { 
    _minimum = n;
}

void            Cylinder::setMaximum(double n) { 
    _maximum = n;
}


void    Cylinder::closed(void) {
    _isClosed = true;
}

void    Cylinder::opened(void) {
    _isClosed = false;
}
