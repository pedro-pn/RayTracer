#include "Gradient.hpp"

Gradient::Gradient(Color const &colorOne, Color const &colorTwo) : Pattern(colorOne, colorTwo) {
}

Color   Gradient::patternAt(Point const &worldPoint) const {
    Color   distance = _colorTwo - _colorOne;
    double  fraction = worldPoint.x - floor(worldPoint.x);
    
    return (_colorOne + (distance * fraction));
}
