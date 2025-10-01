#include "BoundingBox.hpp"

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
