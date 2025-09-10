#include "Stripe.hpp"

Stripe::Stripe(Color const &colorOne, Color const &colorTwo) : _colorOne(colorOne), _colorTwo(colorTwo) {
}

Color   Stripe::patternAt(Point const &point) const {
    if ((static_cast<int>(floor(point.x)) % 2) == 0)
        return (_colorOne);
    return (_colorTwo);
}
