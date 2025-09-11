#pragma once

#include "Pattern.hpp"

class Checker: public Pattern {

    public:

        Checker(Color const &colorOne, Color const &colorTwo);
        ~Checker() = default;

        Color   patternAt(Point const &worldPoint) const override;
};

class CheckerMap: public Pattern {

    public:

        CheckerMap(Color const &colorOne, Color const &colorTwo);
        ~CheckerMap() = default;

        Color   patternAt(Point const &worldPoint) const override;
};
