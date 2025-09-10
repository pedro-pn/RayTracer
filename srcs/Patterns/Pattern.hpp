#pragma once

#include "ColorUtils.hpp"

class Pattern {

    public:

        Pattern(Color const &colorOne, Color const &colorTwo);
        virtual ~Pattern() = default;

        virtual Color   patternAt(Point const &point) const = 0;
        
        void            setTransform(Matrix const &transform);
        Matrix const    &getTransform(void) const;
        Matrix          &getTransform(void);

    protected:

        Matrix  _transform;
        Color   _colorOne;
        Color   _colorTwo;
};
