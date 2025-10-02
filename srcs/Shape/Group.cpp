#include "Group.hpp"
#include <algorithm>

Group::Group() : Shape() {
}

Shape const *   Group::operator[](int index) const {
    return (_children.at(index).get());
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

t_bucket    Group::partitionChildren(void) {
    t_splitted_box boxes = boundsOf().splitBounds();
    t_bucket       bucket;

    for (auto it = _children.begin(); it != _children.end();) {
        if (boxes.left.containsBox((*it)->parentSpaceBoundsOf())) {
            bucket.left.push_back(move(*it));
            it = _children.erase(it);
        }
        else if (boxes.right.containsBox((*it)->parentSpaceBoundsOf())) {
            bucket.right.push_back(move(*it));
            it = _children.erase(it);
        }
        else
            ++it;
    }
    
    return (bucket);
}

void    Group::makeSubgroup(shapeList &shapes) {
    groupPtr    g = make_unique<Group>();
    g->_children.reserve(g->_children.size() + shapes.size());
    g->_children.insert(g->_children.end(), make_move_iterator(shapes.begin()), make_move_iterator(shapes.end()));
    shapes.clear();
    for (auto& ch : g->_children) {
        ch->setParent(g.get());
    }
    addChild(move(g));
}

size_t Group::count(void) const {
    return (_children.size());
}

void    Group::divide(size_t threshold) {
    if (threshold <= this->count()) {
        t_bucket bucket = partitionChildren();
        if (bucket.left.empty() == false)
            makeSubgroup(bucket.left);
        if (bucket.right.empty() == false)
            makeSubgroup(bucket.right);
    }
    for (auto &children : _children) {
        children->divide(threshold);
    }
}
