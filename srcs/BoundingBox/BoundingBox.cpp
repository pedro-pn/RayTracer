#include "BoundingBox.hpp"
#include "Cube.hpp"

BoundingBox::BoundingBox() : _min(point(INFINITY, INFINITY, INFINITY)), _max(point(-INFINITY, -INFINITY, -INFINITY)) {
}

BoundingBox::BoundingBox(Point const &min, Point const &max) : _min(min), _max(max) {
}

BoundingBox BoundingBox::operator+(BoundingBox const &rhs) const {
    BoundingBox box(*this);
    box.addBox(rhs);
    return (box);
}

BoundingBox BoundingBox::operator+(Point const &rhs) const {
    BoundingBox box(*this);
    box.addPoint(rhs);
    return (box);
}


Point const &BoundingBox::getMin(void) const {
    return (_min);
}

Point const &BoundingBox::getMax(void) const {
    return (_max);
}

void        BoundingBox::addPoint(Point const &point) {
    if (point.x < _min.x)
        _min.x = point.x;
    if (point.y < _min.y)
        _min.y = point.y;
    if (point.z < _min.z)
        _min.z = point.z;
    if (point.x > _max.x)
        _max.x = point.x;
    if (point.y > _max.y)
        _max.y = point.y;
    if (point.z > _max.z)
        _max.z = point.z;
}

void        BoundingBox::addBox(BoundingBox const &box) {
    addPoint(box._min);
    addPoint(box._max);
}

bool        BoundingBox::containsPoint(Point const &point) const {
    return (
        point.x >= _min.x && point.x <= _max.x &&
        point.y >= _min.y && point.y <= _max.y &&
        point.z >= _min.z && point.z <= _max.z
    );
}

bool        BoundingBox::containsBox(BoundingBox const &box) const {
    return (containsPoint(box._min) && containsPoint(box._max));
}

BoundingBox BoundingBox::transform(Matrix const &transform) const {
    Point   p1 = _min;
    Point   p2 = point(_min.x, _min.y, _max.z);
    Point   p3 = point(_min.x, _max.y, _min.z);
    Point   p4 = point(_min.x, _max.y, _max.z);
    Point   p5 = point(_max.x, _min.y, _min.z);
    Point   p6 = point(_max.x, _min.y, _max.z);
    Point   p7 = point(_max.x, _max.y, _min.z);
    Point   p8 = _max;

    BoundingBox box;

    box.addPoint(transform * p1);
    box.addPoint(transform * p2);
    box.addPoint(transform * p3);
    box.addPoint(transform * p4);
    box.addPoint(transform * p5);
    box.addPoint(transform * p6);
    box.addPoint(transform * p7);
    box.addPoint(transform * p8);

    return (box);
}

bool BoundingBox::intersect(t_ray const &ray) const {
    t_cube_intersection_t  xIntersect = Cube::_checkAxis(ray.origin.x, ray.direction.x, _min.x, _max.x);
    t_cube_intersection_t  yIntersect = Cube::_checkAxis(ray.origin.y, ray.direction.y, _min.y, _max.y);
    t_cube_intersection_t  zIntersect = Cube::_checkAxis(ray.origin.z, ray.direction.z, _min.z, _max.z);

    double  tmin = max(xIntersect.tmin, max(yIntersect.tmin, zIntersect.tmin));
    double  tmax = min(xIntersect.tmax, min(yIntersect.tmax, zIntersect.tmax));
    if (tmin > tmax)
        return (false);

    return (true);
}

t_splitted_box  BoundingBox::splitBounds(void) const {
    t_splitted_box  boxes;

    double dx = _max.x - _min.x;
    double dy = _max.y - _min.y;
    double dz = _max.z - _min.z;

    double greatest = max(dx, max(dy, dz));

    double x0 = _min.x, y0 = _min.y, z0 = _min.z;
    double x1 = _max.x, y1 = _max.y, z1 = _max.z;
    if (areEqual(greatest, dx)) {
        x0 = x0 + dx / 2.0;
        x1 = x0;
    }
    else if (areEqual(greatest, dy)) {
        y0 = y0 + dy / 2.0;
        y1 = y0;
    }
    else {
        z0 = z0 + dz / 2.0;
        z1 = z0;
    }
    
    Point   midMin = point(x0, y0, z0);
    Point   midMax = point(x1, y1, z1);

    boxes.left = BoundingBox(this->_min, midMax);
    boxes.right = BoundingBox(midMin, this->_max);

    return (boxes);
}
