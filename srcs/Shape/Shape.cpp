#include "Shape.hpp"
#include "Group.hpp"

Shape::Shape(): _transform(Matrix().setIdentity()), _material(t_material()), _parent(nullptr) {
}

Shape::~Shape() {
}

// Shape   &Shape::operator=(Shape const &rhs) {
//     if (this == &rhs)
//         return (*this);
//     this->_material = rhs._material;
//     this->_origin = rhs._origin;
//     this->_transform = rhs._transform;
// }

bool    Shape::operator==(Shape const &rhs) const
{
    return (this->_material == rhs._material && this->_transform == rhs._transform);
}

Matrix const    &Shape::getTransform() const {
    return (this->_transform);
}

Matrix    &Shape::getTransform() {
    return (this->_transform);
}

void    Shape::setTransform(Matrix const &transform) {
    this->_transform = transform;
}

t_material const  &Shape::getMaterial(void) const {
    return (this->_material);
}

t_material  &Shape::getMaterial(void) {
    return (this->_material);
}

void    Shape::setMaterial(t_material const &material) {
    this->_material = material;
}

Color   Shape::patternAt(Point const &worldPoint) const {
    Point   objectPoint = this->_worldToObject(worldPoint);
    Point   patternPoint = _material.pattern->getTransform().inverse() * objectPoint;

    return (this->_material.pattern->patternAt(patternPoint));
}

Vec Shape::_normalToWorld(Vec const &normal) const {
    Vec worldNormal = _transform.transpose().inverse() * normal;
    worldNormal.w = 0;
    worldNormal = worldNormal.normalize();

    if (this->_parent)
        worldNormal = this->_parent->_normalToWorld(worldNormal);
    return (worldNormal);
}

void    Shape::setParent(Group const *group) {
    this->_parent = group;
}

Group   const          *Shape::getParent(void) const {
    return (this->_parent);
}

Point   Shape::_worldToObject(Point const &p) const {
    Point point = p;

    if (this->_parent)
        point = this->_parent->_worldToObject(point);
    
    return (this->_transform.inverse() * point);
}

BoundingBox         Shape::parentSpaceBoundsOf(void) const {
    return (BoundingBox(this->boundsOf()).transform(_transform));
}
