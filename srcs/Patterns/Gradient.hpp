#pragma once

#include "Pattern.hpp"

class Gradient: public Pattern {

    public:

        Gradient(Color const &colorOne, Color const &colorTwo);
        ~Gradient() = default;

        Color   patternAt(Point const &worldPoint) const override;
};
