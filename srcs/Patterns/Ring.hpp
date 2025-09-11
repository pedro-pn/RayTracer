#pragma once

#include "Pattern.hpp"

class Ring: public Pattern {

    public:

        Ring(Color const &colorOne, Color const &colorTwo);
        ~Ring() = default;

        Color   patternAt(Point const &worldPoint) const;
};
