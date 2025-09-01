#include "RayTracer.hpp"

Sphere::Sphere(): _origin(point(0, 0, 0)), _transform(Matrix().setIdentity()) {
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