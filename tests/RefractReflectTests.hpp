#pragma once

#include <UnitTest++/UnitTest++.h>
#include "RayTracer.hpp"

SUITE (REFLECTIVE_TESTS) {

    TEST(reflectivity_for_default_material) {
        t_material  m;

        CHECK(m.reflective == 0.0);
    }

    TEST(precomputing_reflection_vector) {
        Plane   p;
        t_ray   r = ray(point(0, 1, -1), vec(0, -sqrt(2) / 2, sqrt(2) / 2));
        
        t_intersection  inter = intersection(sqrt(2), p);
        t_computations comps = prepareComputations(inter, r);

        CHECK(comps.reflectv == vec(0, sqrt(2) / 2, sqrt(2) / 2));
    }

    TEST(reflected_color_for_nonreflective_material) {
        World   w = defaultWorld();
        t_ray   r = ray(point(0, 0, 0), vec(0, 0, 1));

        w.getShapes()[1]->getMaterial().ambient = 1;;
        
        t_intersection  inter = intersection(sqrt(2), *w.getShapes()[1]);
        t_computations comps = prepareComputations(inter, r);
        Color       c = reflectedColor(w, comps, REMAINING);
        CHECK(c == color(0, 0, 0));
    }

    TEST(reflected_color_for_reflective_material) {
        World   w = defaultWorld();
        t_ray   r = ray(point(0, 0, -3), vec(0, -sqrt(2) / 2, sqrt(2) / 2));
        shapePtr   p = make_unique<Plane>();
        p->getMaterial().reflective = 0.5;
        p->getTransform().translate(0, -1, 0);

        w.addShape(std::move(p));
        
        t_intersection  inter = intersection(sqrt(2), *w.getShapes()[2]);
        t_computations comps = prepareComputations(inter, r);
        Color       c = reflectedColor(w, comps, REMAINING);
        CHECK(c == color(0.19032, 0.2379, 0.14274));
    }

    TEST(shadeHit_with_reflective_material) {
        World   w = defaultWorld();
        t_ray   r = ray(point(0, 0, -3), vec(0, -sqrt(2) / 2, sqrt(2) / 2));
        shapePtr   p = make_unique<Plane>();
        p->getMaterial().reflective = 0.5;
        p->getTransform().translate(0, -1, 0);

        w.addShape(std::move(p));
        
        t_intersection  inter = intersection(sqrt(2), *w.getShapes()[2]);
        t_computations comps = prepareComputations(inter, r);
        Color       c = shadeHit(w, comps, 1);
        CHECK(c == color(0.87677, 0.92436, 0.82918));
    }

    TEST(colorAt_with_mutually_reflective_surfaces) {
        World   w = World();
        w.setLight(pointLight(point(0, 0, 0), color (1, 1, 1)));
        shapePtr    lower = make_unique<Plane>();
        lower->getMaterial().reflective = 1;
        lower->getTransform().translate(0, -1, 0);

        shapePtr    upper = make_unique<Plane>();
        upper->getMaterial().reflective = 1;
        upper->getTransform().translate(0, 1, 0);

        w.addShape(std::move(lower));
        w.addShape(std::move(upper));
        
        t_ray   r = ray(point(0, 0, 0), vec(0, 1, 0));

        UNITTEST_TIME_CONSTRAINT(50);
        colorAt(w, r, 0);
    }
}