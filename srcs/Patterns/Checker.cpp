#include "Checker.hpp"

Checker::Checker(Color const &colorOne, Color const &colorTwo): Pattern(colorOne, colorTwo) {
}

Color   Checker::patternAt(Point const &worldPoint) const {
    if ((static_cast<int>(floor(worldPoint.x)) + static_cast<int>(floor(worldPoint.y))+ static_cast<int>(floor(worldPoint.z))) % 2 == 0 )
        return (_colorOne);
    return (_colorTwo);
}

CheckerMap::CheckerMap(Color const &colorOne, Color const &colorTwo): Pattern(colorOne, colorTwo) {
}

Color   CheckerMap::patternAt(Point const &worldPoint) const {
    double y = std::max(-1.0, std::min(1.0, worldPoint.y));
    double u = (std::atan2(worldPoint.x, worldPoint.z) + M_PI) / M_PI / 2;
    double v = std::acos(y) / M_PI;
    int checksU = 8;
    int checksV = 4;

    u = std::fmod(u + EPSILON, 1.0);
    v = std::min(v + EPSILON, 1.0 - EPSILON);
    int iu = static_cast<int>(std::floor(u * checksU));
    int iv = static_cast<int>(std::floor(v * checksV));
    if ( ( (iu + iv) & 1 ) == 0 )
        return _colorOne;

    return _colorTwo;
}
