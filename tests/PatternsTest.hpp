#pragma once 

#include "UnitTest++/UnitTest++.h"
#include "RayTracer.hpp"

using namespace ColorUtils;

SUITE(PATTERNS_TEST) {

    TEST(stripe_pattern_is_constant_in_y) {
        Stripe pattern = Stripe(white(), black());

        CHECK(pattern.patternAt(point(0, 0, 0)) == white());
        CHECK(pattern.patternAt(point(0, 1, 0)) == white());
        CHECK(pattern.patternAt(point(0, 2, 0)) == white());
    }

    TEST(stripe_pattern_is_constant_in_z) {
        Stripe pattern = Stripe(white(), black());

        CHECK(pattern.patternAt(point(0, 0, 0)) == white());
        CHECK(pattern.patternAt(point(0, 0, 1)) == white());
        CHECK(pattern.patternAt(point(0, 0, 2)) == white());
    }

    TEST(stripe_pattern_alternates_in_x) {
        Stripe pattern = Stripe(white(), black());

        CHECK(pattern.patternAt(point(0, 0, 0)) == white());
        CHECK(pattern.patternAt(point(0.9, 0, 0)) == white());
        CHECK(pattern.patternAt(point(1, 0, 0)) == black());
        CHECK(pattern.patternAt(point(-0.1, 0, 0)) == black());
        CHECK(pattern.patternAt(point(-1, 0, 0)) == black());
        CHECK(pattern.patternAt(point(-1.1, 0, 0)) == white());
    }

    TEST(lighting_with_a_pattern_applied) {
        t_material  m = t_material();
        m.pattern = make_shared<Stripe>(white(), black());
        m.ambient = 1;
        m.diffuse = 0;
        m.specular = 0;
        Vec eyev = vec(0, 0, -1);
        Vec normalv(vec(0, 0, -1));
        t_light light = pointLight(point(0, 0, -10), color(1, 1, 1));

        Color   c1 = lighting(m, light, point(0.9, 0, 0), eyev, normalv, false);
        Color   c2 = lighting(m, light, point(1.1, 0, 0), eyev, normalv, false);

        CHECK(c1 == color(1, 1, 1));
        CHECK(c2 == color(0, 0, 0));
    }
}
