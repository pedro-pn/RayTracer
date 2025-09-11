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
        Sphere  s = Sphere();
        t_material  m = t_material();
        m.pattern = make_shared<Stripe>(white(), black());
        m.ambient = 1;
        m.diffuse = 0;
        m.specular = 0;
        s.setMaterial(m);
        Vec eyev = vec(0, 0, -1);
        Vec normalv(vec(0, 0, -1));
        t_light light = pointLight(point(0, 0, -10), color(1, 1, 1));

        Color   c1 = lighting(s, light, point(0.9, 0, 0), eyev, normalv, false);
        Color   c2 = lighting(s, light, point(1.1, 0, 0), eyev, normalv, false);

        CHECK(c1 == color(1, 1, 1));
        CHECK(c2 == color(0, 0, 0));
    }

    TEST(stripes_with_an_object_transformation) {
        t_material  m = t_material();
        Sphere  s = Sphere();
        s.setTransform(scaling(2, 2, 2));
        m.pattern = make_shared<Stripe>(white(), black());
        s.setMaterial(m);
        Color   c = s.patternAt(point(1.5, 0, 0));
        
        CHECK(c == white());
    }
    
    TEST(stripes_with_a_pattern_transformation) {
        t_material  m = t_material();
        Sphere  s = Sphere();
        m.pattern = make_shared<Stripe>(white(), black());
        m.pattern->setTransform(scaling(2, 2, 2));
        s.setMaterial(m);
        Color   c = s.patternAt(point(1.5, 0, 0));

        CHECK(c == white());
    }
    
    TEST(stripes_with_both_pattern_and_object_transformation) {
        t_material  m = t_material();
        Sphere  s = Sphere();
        s.setTransform(scaling(2, 2, 2));
        m.pattern = make_shared<Stripe>(white(), black());
        m.pattern->setTransform(translation(0.5, 0, 0));
        s.setMaterial(m);
        Color   c = s.patternAt(point(2.5, 0, 0));

        CHECK(c == white());
    }
    
    TEST(gradient_linearly_interpolates_between_colors) {
        t_material  m = t_material();
        Sphere  s = Sphere();
        m.pattern = make_shared<Gradient>(white(), black());
        s.setMaterial(m);

        CHECK(s.patternAt(point(0, 0, 0)) == white());
        CHECK(s.patternAt(point(0.25, 0, 0)) == color(0.75, 0.75, 0.75));
        CHECK(s.patternAt(point(0.5, 0, 0)) == color(0.5, 0.5, 0.5));
        CHECK(s.patternAt(point(0.75, 0, 0)) == color(0.25, 0.25, 0.25));
    }
    
    TEST(ring_should_extend_in_both_x_and_z) {
        t_material  m = t_material();
        Sphere  s = Sphere();
        m.pattern = make_shared<Ring>(white(), black());
        s.setMaterial(m);

        CHECK(s.patternAt(point(0, 0, 0)) == white());
        CHECK(s.patternAt(point(1, 0, 0)) == black());
        CHECK(s.patternAt(point(0, 0, 1)) == black());
        CHECK(s.patternAt(point(0.708, 0, 0.708)) == black());
    }

}
