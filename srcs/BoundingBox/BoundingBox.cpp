#include "BoundingBox.hpp"

BoundingBox::BoundingBox() : _min(point(INFINITY, INFINITY, INFINITY)), _max(point(-INFINITY, -INFINITY, -INFINITY)) {
}

BoundingBox::BoundingBox(Point const &min, Point const &max) : _min(min), _max(max) {
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
