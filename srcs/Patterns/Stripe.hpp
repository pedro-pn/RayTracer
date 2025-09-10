#pragma once

#include "Pattern.hpp"

class Stripe: public Pattern {

    public:

        Stripe(Color const &colorOne, Color const &colorTwo);
        ~Stripe() = default;

        Color   patternAt(Point const &point) const override;
};
