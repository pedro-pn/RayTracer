#include "Ring.hpp"

Ring::Ring(Color const &colorOne, Color const &colorTwo): Pattern(colorOne, colorTwo) {
}

Color   Ring::patternAt(Point const &worldPoint) const {
    if ((static_cast<int>((floor(sqrt(pow(worldPoint.x, 2) + pow(worldPoint.z, 2))))) % 2) == 0)
        return (_colorOne);
    return (_colorTwo);
}