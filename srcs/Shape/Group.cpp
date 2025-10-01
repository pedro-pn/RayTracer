#include "Group.hpp"
#include <algorithm>

Group::Group() : Shape() {
}

Shape const *   Group::operator[](int index) const {
    return (&*this->_children[index]);
}

t_intersect Group::intersect(t_ray const &ray) const {
    t_intersect xs;
    t_ray       r = transformRay(ray, this->getTransform().inverse());

    xs.count = 0;
    if (boundsOf().intersect(r) == false)
        return (xs);
    for (auto it = _children.begin(); it != _children.end(); it++) {
        xs += (*it)->intersect(r);
    }
    sort(xs.intersections.begin(), xs.intersections.end());
    return (xs);
}

Vec Group::normalAt(Point const &worldPoint) const {
    (void)worldPoint;
    throw std::logic_error("Group cannot calculate normal vector");
}

void    Group::addChild(shapePtr shape) {
    shape->setParent(this);
    this->_children.push_back(std::move(shape));
}

BoundingBox Group::boundsOf(void) const {
    BoundingBox box;

    for (auto it = _children.begin(); it != _children.end(); it++) {
        BoundingBox cbox = (*it)->parentSpaceBoundsOf();
        box = box + cbox;
    }
    return (box);
}
