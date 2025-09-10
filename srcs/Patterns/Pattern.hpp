#pragma once

#include "ColorUtils.hpp"

class Pattern {

    public:

        Pattern();
        virtual ~Pattern() = default;

        virtual Color   patternAt(Point const &point) const = 0;
        
        void            setTransform(Matrix const &transform);
        Matrix const    &getTransform(void) const;
        Matrix          &getTransform(void);

    private:

        Matrix  _transform;
};
