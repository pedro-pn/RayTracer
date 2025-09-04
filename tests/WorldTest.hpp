#pragma once

#include <UnitTest++/UnitTest++.h>
#include "TestUtils.hpp"
#include "RayTracer.hpp"

SUITE(WORLD_TESTS) {

    TEST(default_world) {
        t_light light = pointLight(point(-10, 10, -10), color(1, 1, 1));
        Sphere  s1 = Sphere();
        t_material  m = t_material();
        m.colour = color(0.8, 1.0, 0.6);
        m.diffuse = 0.7,
        m.specular = 0.2;
        s1.setMaterial(m);
        Sphere s2 = Sphere();
        s2.setTransform(Matrix().setIdentity().scale(0.5, 0.5, 0.5));

        World   w = defaultWorld();

        CHECK(w.getLight() == light);
        CHECK(w.getObjects()[0] == s1);
        CHECK(w.getObjects()[1] == s2);

    }

    TEST(intersect_world_with_a_ray) {
        World   w = defaultWorld();
        t_ray   r = ray(point(0, 0, -5), vec(0, 0, 1));
        t_intersect xs = w.intersectWorld(r);

        CHECK(xs.count == 4);
        CHECK(xs.intersections[0].t == 4);
        CHECK(xs.intersections[1].t == 4.5);
        CHECK(xs.intersections[2].t == 5.5);
        CHECK(xs.intersections[3].t == 6);
    }

    TEST(precomputing_state_of_intersection) {
        t_ray   r = ray(point(0, 0, -5), vec(0, 0, 1));
        Sphere  s;
        t_intersection  inter = intersection(4, s);

        t_computations   comps = prepareComputations(inter, r);

        CHECK(comps.t == inter.t);
        CHECK(comps.object == inter.object);
        CHECK(comps.point == point(0, 0, -1));
        CHECK(comps.eyev == vec(0, 0, -1));
        CHECK(comps.normalv == vec(0, 0, -1));
    }

    TEST(hit_when_an_intersection_occurs_on_the_outside) {
        t_ray   r = ray(point(0, 0, -5), vec(0, 0, 1));
        Sphere  s;
        t_intersection  inter = intersection(4, s);

        t_computations   comps = prepareComputations(inter, r);

        CHECK(comps.inside == false);
    }

    TEST(hit_when_an_intersection_occurs_on_the_inside) {
        t_ray   r = ray(point(0, 0, 0), vec(0, 0, 1));
        Sphere  s;
        t_intersection  inter = intersection(1, s);

        t_computations   comps = prepareComputations(inter, r);

        CHECK(comps.point == point(0, 0, 1));
        CHECK(comps.eyev == vec(0, 0, -1));
        CHECK(comps.inside == true);
        CHECK(comps.normalv == vec(0, 0, -1));
    }

    TEST(shading_an_intersection) {
        t_ray   r = ray(point(0, 0, -5), vec(0, 0, 1));
        World   w = defaultWorld();
        t_intersection  inter = intersection(4, w.getObjects()[0]);

        
        t_computations   comps = prepareComputations(inter, r);
        Color   c = shadeHit(w, comps);

        CHECK(c == color(0.38066, 0.47583, 0.2855));
    }
    
    TEST(shading_an_intersection_from_the_inside) {
        t_ray   r = ray(point(0, 0, 0), vec(0, 0, 1));
        Sphere  s;
        t_intersection  inter = intersection(0.5, s);
        World   w = defaultWorld();
        w.setLight(pointLight(point(0, 0.25, 0), color(1, 1, 1)));
        
        
        
        t_computations   comps = prepareComputations(inter, r);
        Color   c = shadeHit(w, comps);
        
        CHECK(c == color(0.90498, 0.90498, 0.90498));
    }

    TEST(color_when_ray_misses) {
        World   w = defaultWorld();
        t_ray   r = ray(point(0, 0, -5), vec(0, 1, 0));

        Color   c = colorAt(w, r);

        CHECK(c == color(0, 0, 0));
    }

    TEST(color_when_ray_hits) {
        World   w = defaultWorld();
        t_ray   r = ray(point(0, 0, -5), vec(0, 0, 1));

        Color   c = colorAt(w, r);

        CHECK(c == color(0.38066, 0.47583, 0.2855));
    }

    TEST(color_with_intersection_behind_the_ray) {
        World   w = defaultWorld();

        w.getObjects()[0].getMaterial().ambient = 1;
        w.getObjects()[1].getMaterial().ambient = 1;

        t_ray   r = ray(point(0, 0, 0.75), vec(0, 0, -1));

        Color   c = colorAt(w, r);

        CHECK(c ==  w.getObjects()[1].getMaterial().colour);
    }
}