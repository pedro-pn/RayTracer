#include "Cone.hpp"

Cone::Cone() : Cylinder() {
}

bool    Cone::_checkCap(t_ray const &ray, double t, double y) const {
    double x = ray.origin.x + t * ray.direction.x;
    double z = ray.origin.z + t * ray.direction.z;

    return ((pow(x, 2) + pow(z, 2)) <= pow(y, 2));
}

void    Cone::_intersectCaps(t_ray const &ray, t_intersect &xs) const {
    if (_isClosed == false || areEqual(ray.direction.y, 0))
        return ;
    
    double  t = (_minimum - ray.origin.y) / ray.direction.y;
    if (_checkCap(ray, t, _minimum))
        createIntersection(xs, intersection(t, *this));

    t = (_maximum - ray.origin.y) / ray.direction.y;
    if (_checkCap(ray, t, _maximum))
        createIntersection(xs, intersection(t, *this));
}

void    Cone::_intersectWalls(t_ray const &ray, t_intersect &xs) const {
    double  a = pow(ray.direction.x, 2) -  pow(ray.direction.y, 2) + pow(ray.direction.z, 2);
    double  b = 2 * ray.origin.x * ray.direction.x - 2 * ray.origin.y * ray.direction.y + 2 * ray.origin.z * ray.direction.z;
    double  c = pow(ray.origin.x, 2) - pow(ray.origin.y, 2) + pow(ray.origin.z, 2);
    double  discriminant = pow(b, 2) - 4 * a * c;
    double  t;

    if (areEqual(a, 0)) {
        if (areEqual(b, 0))
            return ;
        else if (areEqual(b, 0) == false) {
            t = -c / (2 * b);
            createIntersection(xs, intersection(t, *this));
            return ;
        }
    }
    
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

t_intersect Cone::intersect(t_ray const &ray) const {
    t_ray   transformedRay = transformRay(ray, this->getTransform().inverse());
    t_intersect xs;
    
    xs.count = 0;
    _intersectWalls(transformedRay, xs);
    _intersectCaps(transformedRay, xs);
        
    return (xs);
}

Vec Cone::normalAt(Point const &worldPoint) const {
    Point   objectPoint = this->getTransform().inverse() * worldPoint;
    double  dist = pow(objectPoint.x, 2) + pow(objectPoint.z, 2);

    if (dist < 1 && objectPoint.y >= (_maximum - EPSILON))
        return (_normalToWorld(vec(0, 1, 0)));
    else if (dist < 1 && objectPoint.y <= (_minimum + EPSILON))
        return (_normalToWorld(vec(0, -1, 0)));
    double y = sqrt(pow(objectPoint.x, 2) + pow(objectPoint.z, 2));
    if (objectPoint.y > 0)
        y = -y;

    return (_normalToWorld(vec(objectPoint.x, y, objectPoint.z)));
}
