#include "Triangle.hpp"

Triangle::Triangle() : _p1(point(0, 1, 0)), _p2(point(-1, 0, 0)), _p3(point(1, 0, 0)) {
    _initializeTriangle(_p1, _p2, _p3);
}

Triangle::Triangle(Point const &p1, Point const &p2, Point const &p3) : _p1(p1), _p2(p2), _p3(p3) {
    _initializeTriangle(p1, p2, p3);
}

void   Triangle::_initializeTriangle(Point const &p1, Point const &p2, Point const &p3) {
    _e1 = p2 - p1;
    _e2 = p3 - p1;
    _normal = cross(_e2, _e1).normalize();
}

Point const Triangle::p1(void) const {
    return (this->_p1);
}

Point const Triangle::p2(void) const {
    return (this->_p2);
}

Point const Triangle::p3(void) const {
    return (this->_p3);
}

Point const Triangle::e1(void) const {
    return (this->_e1);
}

Point const Triangle::e2(void) const {
    return (this->_e2);
}

Vec const   Triangle::normal(void) const {
    return (this->_normal);
}

t_intersect Triangle::intersect(t_ray const &r) const {
    t_ray transformedRay = transformRay(r, getTransform().inverse());
    t_intersect xs;

    Vec dirCrossE2 = cross(transformedRay.direction, _e2);
    double det = dot(_e1, dirCrossE2);

    if (abs(det) < EPSILON)
        return (xs);
    double f = 1.0 / det;
    Vec p1ToOrigin = transformedRay.origin - _p1;
    double u = f * dot(p1ToOrigin, dirCrossE2);
    if (u < 0 || u > 1)
        return (xs);
    Vec originCrossE1 = cross(p1ToOrigin, _e1);
    double v = f * dot(transformedRay.direction, originCrossE1);
    if (v < 0 || (u + v) > 1)
        return (xs);
    double t = f * dot(_e2, originCrossE1);
    createIntersection(xs, intersection(t, *this));
    return (xs);
}

Vec         Triangle::normalAt(Point const &worldPoint) const {
    (void)worldPoint;
    return (_normalToWorld(_normal));
}

BoundingBox Triangle::boundsOf(void) const {
    BoundingBox box;
    return (box);
}
