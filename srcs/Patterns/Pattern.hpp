#pragma once

#include "ColorUtils.hpp"

class Pattern {

    public:

        Pattern() = default;
        virtual ~Pattern() = default;

        virtual Color   patternAt(Point const &point) const = 0;
};
