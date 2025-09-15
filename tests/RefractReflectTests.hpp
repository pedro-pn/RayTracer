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
        t_intersect xs;
		xs.count = 0;
        t_computations comps = prepareComputations(inter, r, xs);

        CHECK(comps.reflectv == vec(0, sqrt(2) / 2, sqrt(2) / 2));
    }

    TEST(reflected_color_for_nonreflective_material) {
        World   w = defaultWorld();
        t_ray   r = ray(point(0, 0, 0), vec(0, 0, 1));

        w.getShapes()[1]->getMaterial().ambient = 1;;
        
        t_intersection  inter = intersection(sqrt(2), *w.getShapes()[1]);
        t_intersect xs;
		xs.count = 0;
        t_computations comps = prepareComputations(inter, r, xs);
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
        t_intersect xs;
		xs.count = 0;
        t_computations comps = prepareComputations(inter, r, xs);
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
        t_intersect xs;
		xs.count = 0;
        t_computations comps = prepareComputations(inter, r, xs);
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

SUITE(REFRACTIVE_TESTS) {
    
    TEST(transparency_and_refractive_index_for_default_material) {
        t_material  m;

        CHECK(areEqual(m.refractiveIndex, 1.0));
        CHECK(m.transparency == 0);
    }

    TEST(helper_function_for_producing_glass_sphere) {
        Sphere s = glassSphere();

        CHECK(s.getTransform() == Matrix().setIdentity());
        CHECK(areEqual(s.getMaterial().transparency, 1.0));
        CHECK(areEqual(s.getMaterial().refractiveIndex, 1.5));
    }

    TEST(finding_n1_and_n2_at_various_intersections) {
        Sphere a = glassSphere();
        a.getTransform().scale(2, 2, 2);
        
        Sphere b = glassSphere();
        b.getTransform().translate(0, 0, -0.25);
        b.getMaterial().refractiveIndex = 2.0;

        Sphere c = glassSphere();
        c.getTransform().translate(0, 0, 0.25);
        c.getMaterial().refractiveIndex = 2.5;

        t_ray   r = ray(point(0, 0, -4), vec(0, 0, 1));
        t_intersect xs;

        xs.intersections.push_back(intersection(2, a));
        xs.intersections.push_back(intersection(2.75, b));
        xs.intersections.push_back(intersection(3.25, c));
        xs.intersections.push_back(intersection(4.75, b));
        xs.intersections.push_back(intersection(5.25, c));
        xs.intersections.push_back(intersection(6, a));
        xs.count = 6;

        t_computations comps = prepareComputations(xs.intersections[0], r, xs);
        CHECK(areEqual(comps.n1, 1.0));
        CHECK(areEqual(comps.n2, 1.5));

        comps = prepareComputations(xs.intersections[1], r, xs);
        CHECK(areEqual(comps.n1, 1.5));
        CHECK(areEqual(comps.n2, 2.0));

        comps = prepareComputations(xs.intersections[2], r, xs);
        CHECK(areEqual(comps.n1, 2.0));
        CHECK(areEqual(comps.n2, 2.5));

        comps = prepareComputations(xs.intersections[3], r, xs);
        CHECK(areEqual(comps.n1, 2.5));
        CHECK(areEqual(comps.n2, 2.5));

        comps = prepareComputations(xs.intersections[4], r, xs);
        CHECK(areEqual(comps.n1, 2.5));
        CHECK(areEqual(comps.n2, 1.5));

        comps = prepareComputations(xs.intersections[5], r, xs);
        CHECK(areEqual(comps.n1, 1.5));
        CHECK(areEqual(comps.n2, 1.0));
    }

    TEST(under_point_is_offset_below_the_surface) {
        t_ray r = ray(point(0, 0, -5), vec(0, 0, 1));
        Sphere  s = glassSphere();
        s.getTransform().translate(0, 0, 1);
        t_intersection inter = intersection(5, s);
        t_intersect xs;
        xs.intersections.push_back(inter);
        t_computations comps = prepareComputations(inter, r, xs);

        CHECK(comps.underPoint.z > (EPSILON / 2));
        CHECK(comps.point.z < comps.underPoint.z);
    }

    TEST(refracted_color_with_an_opaque_surface) {
        World w = defaultWorld();
        Shape const *s1 = &*w.getShapes()[0];

        t_ray r = ray(point(0, 0, -5), vec(0, 0, 1));
        t_intersect xs;
        xs.intersections.push_back(intersection(4, *s1));
        xs.intersections.push_back(intersection(6, *s1));
        xs.count = 2;

        t_computations comps = prepareComputations(xs.intersections[0], r, xs);
        Color   c = refractedColor(w, comps, 5);

        CHECK(c == color(0, 0, 0));
    }

    TEST(refracted_color_at_the_maximum_recursive_depth) {
        World w = defaultWorld();
        Shape *s1 = &*w.getShapes()[0];
        s1->getMaterial().transparency = 1.0;
        s1->getMaterial().refractiveIndex = 1.5;

        t_ray r = ray(point(0, 0, -5), vec(0, 0, 1));
        t_intersect xs;
        xs.intersections.push_back(intersection(4, *s1));
        xs.intersections.push_back(intersection(6, *s1));
        xs.count = 2;

        t_computations comps = prepareComputations(xs.intersections[0], r, xs);
        Color   c = refractedColor(w, comps, 0);

        CHECK(c == color(0, 0, 0));
    }

    TEST(refracted_color_under_total_internal_reflection) {
        World w = defaultWorld();
        Shape *s1 = &*w.getShapes()[0];
        s1->getMaterial().transparency = 1.0;
        s1->getMaterial().refractiveIndex = 1.5;

        t_ray r = ray(point(0, 0, sqrt(2) / 2), vec(0, 1, 0));
        t_intersect xs;
        xs.intersections.push_back(intersection(-sqrt(2) / 2, *s1));
        xs.intersections.push_back(intersection(sqrt(2) / 2, *s1));
        xs.count = 2;

        t_computations comps = prepareComputations(xs.intersections[1], r, xs);
        Color   c = refractedColor(w, comps, 5);

        CHECK(c == color(0, 0, 0));
    }

    // TEST(refracted_color_with_a_refracted_ray) {
    //     World   w = defaultWorld();

    //     Shape *s = &*w.getShapes()[0];
    //     s->getMaterial().ambient = 1.0;
    //     // s->getMaterial().pattern = make_shared<Stripe>(white(), black());
    //     // s->getMaterial().pattern->setTransform(translation(0.5, 0, 0));

    //     Shape *b = &*w.getShapes()[1];
    //     b->getMaterial().transparency = 1.0;
    //     b->getMaterial().refractiveIndex = 1.5;

    //     t_ray   r = ray(point(0, 0, 0.1), vec(0, 1, 0));
    //     t_intersection i1 = intersection(-0.9899, *s);
    //     t_intersection i2 = intersection(-0.4899, *b);
    //     t_intersection i3 = intersection(0.4899, *b);
    //     t_intersection i4 = intersection(0.9899, *s);

    //     t_intersect xs;
    //     xs.count = 4;
    //     xs.intersections.push_back(i1);
    //     xs.intersections.push_back(i2);
    //     xs.intersections.push_back(i3);
    //     xs.intersections.push_back(i4);

    //     t_computations comps = prepareComputations(xs.intersections[2], r, xs);
    //     Color   c = refractedColor(w, comps, 5);

    //     cout << "color: " << c << endl;
    //     CHECK(c == color(0, 0.99888, 0.04725));
    // }

    TEST(shade_hit_with_transparent_material) {
        World w = defaultWorld();
        w.addShape(make_unique<Plane>());
        Shape *floor = &*w.getShapes()[2];
        floor->getTransform().translate(0, -1, 0);
        floor->getMaterial().transparency = 0.5;
        floor->getMaterial().refractiveIndex = 1.5;

        w.addShape(make_unique<Sphere>());
        Shape *ball = &*w.getShapes()[3];
        ball->getTransform().translate(0, -3.5, -0.5);
        ball->getMaterial().colour = color(1, 0, 0);
        ball->getMaterial().ambient = 0.5;

        t_ray   r = ray(point(0, 0, -3), vec(0, -sqrt(2) /2, sqrt(2) / 2));
        t_intersect xs;

        t_intersection i1 = intersection(sqrt(2), *floor);
        xs.count = 1;
        xs.intersections.push_back(i1);

        t_computations comps = prepareComputations(i1, r, xs);
        Color   c = shadeHit(w, comps, 5);

        CHECK(c == color(0.93642, 0.68642, 0.68642));
    }
    
    TEST(schlick_approximation_under_total_internal_reflection) {
        Sphere  s = glassSphere();
        
        t_ray   r = ray(point(0, 0, sqrt(2) / 2), vec(0, 1, 0));
        t_intersect xs;
        
        t_intersection i1 = intersection(-sqrt(2) / 2, s);
        t_intersection i2 = intersection(sqrt(2) / 2, s);
        
        xs.count = 2;
        xs.intersections.push_back(i1);
        xs.intersections.push_back(i2);
        
        t_computations  comps = prepareComputations(xs.intersections[1], r, xs);
        double  reflectance = schlick(comps);
        
        CHECK(areEqual(reflectance, 1.0));
    }
    
    TEST(schlick_approximation_with_a_perpendicular_viewing_angle) {
        Sphere  s = glassSphere();
        
        t_ray   r = ray(point(0, 0, 0), vec(0, 1, 0));
        t_intersect xs;
        
        t_intersection i1 = intersection(-1, s);
        t_intersection i2 = intersection(1, s);
        
        xs.count = 2;
        xs.intersections.push_back(i1);
        xs.intersections.push_back(i2);
        
        t_computations  comps = prepareComputations(xs.intersections[1], r, xs);
        double  reflectance = schlick(comps);

        CHECK(areEqual(reflectance, 0.04));
    }
    
    TEST(schlick_approximation_with_small_angle_and_n2_greater_than_n2) {
        Sphere  s = glassSphere();
        
        t_ray   r = ray(point(0, 0.99, -2), vec(0, 0, 1));
        t_intersect xs;
        
        t_intersection i1 = intersection(1.8589, s);
        
        xs.count = 1;
        xs.intersections.push_back(i1);
        
        t_computations  comps = prepareComputations(xs.intersections[0], r, xs);
        double  reflectance = schlick(comps);
        
        CHECK(areEqual(reflectance, 0.48873));
    }
    
    TEST(shade_hit_with_reflective_transparent_material) {
        World w = defaultWorld();
        w.addShape(make_unique<Plane>());
        Shape *floor = &*w.getShapes()[2];
        floor->getTransform().translate(0, -1, 0);
        floor->getMaterial().transparency = 0.5;
        floor->getMaterial().reflective = 0.5;
        floor->getMaterial().refractiveIndex = 1.5;

        w.addShape(make_unique<Sphere>());
        Shape *ball = &*w.getShapes()[3];
        ball->getTransform().translate(0, -3.5, -0.5);
        ball->getMaterial().colour = color(1, 0, 0);
        ball->getMaterial().ambient = 0.5;

        t_ray   r = ray(point(0, 0, -3), vec(0, -sqrt(2) /2, sqrt(2) / 2));
        t_intersect xs;

        t_intersection i1 = intersection(sqrt(2), *floor);
        xs.count = 1;
        xs.intersections.push_back(i1);

        t_computations comps = prepareComputations(i1, r, xs);
        Color   c = shadeHit(w, comps, 5);

        CHECK(c == color(0.93391, 0.69643, 0.69243));
    }
}
