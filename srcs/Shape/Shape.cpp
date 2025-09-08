#include "Shape.hpp"

Shape::Shape(): _origin(point(0, 0, 0)), _transform(Matrix().setIdentity()), _material(t_material()) {
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

Point   Shape::getOrigin(void) const {
    return (this->_origin);
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
