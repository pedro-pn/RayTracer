#include "Pattern.hpp"

Pattern::Pattern(void) {
    _transform.setIdentity();
}

void    Pattern::setTransform(Matrix const &transform) {
    this->_transform = transform;
}

Matrix const    &Pattern::getTransform(void) const {
    return (this->_transform);
}

Matrix    &Pattern::getTransform(void) {
    return (this->_transform);
}
