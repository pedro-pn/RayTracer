#include "Sphere.hpp"

Sphere::Sphere(): _origin(point(0, 0, 0)), _transform(Matrix().setIdentity()), _material(t_material()) {
}

Sphere::~Sphere() {
}

// bool    Sphere::operator==(Sphere const &rhs) const
// {
//     if (*this == rhs)
//         return (true);
//     return (false);
// };

Matrix const    &Sphere::getTransform() const {
    return (this->_transform);
}

void    Sphere::setTransform(Matrix const &transform) {
    this->_transform = transform;
}

Point   Sphere::getOrigin(void) const {
    return (this->_origin);
}

t_material const  &Sphere::getMaterial(void) const {
    return (this->_material);
}

void    Sphere::setMaterial(t_material const &material) {
    this->_material = material;
}
