#pragma once

#include "RayTracer.hpp"
#include <UnitTest++/UnitTest++.h>

SUITE(CUBE_TESTS) {

    TEST(ray_intersect_a_cube) {
        Cube    c;
        
        t_ray   r = ray(point(5, 0.5, 0), vec(-1, 0, 0));
        t_intersect xs = c.intersect(r);
        CHECK(areEqual(xs.intersections[0].t, 4));
        CHECK(areEqual(xs.intersections[1].t, 6));

        r = ray(point(-5, 0.5, 0), vec(1, 0, 0));
        xs = c.intersect(r);
        CHECK(areEqual(xs.intersections[0].t, 4));
        CHECK(areEqual(xs.intersections[1].t, 6));

        r = ray(point(0.5, 5, 0), vec(0, -1, 0));
        xs = c.intersect(r);
        CHECK(areEqual(xs.intersections[0].t, 4));
        CHECK(areEqual(xs.intersections[1].t, 6));

        r = ray(point(0.5, -5, 0), vec(0, 1, 0));
        xs = c.intersect(r);
        CHECK(areEqual(xs.intersections[0].t, 4));
        CHECK(areEqual(xs.intersections[1].t, 6));

        r = ray(point(0.5, 0, 5), vec(0, 0, -1));
        xs = c.intersect(r);
        CHECK(areEqual(xs.intersections[0].t, 4));
        CHECK(areEqual(xs.intersections[1].t, 6));

        r = ray(point(0.5, 0, -5), vec(0, 0, 1));
        xs = c.intersect(r);
        CHECK(areEqual(xs.intersections[0].t, 4));
        CHECK(areEqual(xs.intersections[1].t, 6));

        r = ray(point(0, 0.5, 0), vec(0, 0, 1));
        xs = c.intersect(r);
        CHECK(areEqual(xs.intersections[0].t, -1));
        CHECK(areEqual(xs.intersections[1].t, 1));
    }

    TEST(ray_misses_a_cube) {
        Cube    c;
        
        t_ray   r = ray(point(-2, 0, 0), vec(0.2673, 0.5345, 0.8018));
        t_intersect xs = c.intersect(r);
        CHECK(xs.intersections.empty() == true);
        CHECK(xs.count == 0);
        
        r = ray(point(0, -2, 0), vec(0.8018, 0.2673, 0.5345));
        xs = c.intersect(r);
        CHECK(xs.intersections.empty() == true);
        CHECK(xs.count == 0);
        
        r = ray(point(0, 0, -2), vec(0.5345, 0.8018, 0.2673));
        xs = c.intersect(r);
        CHECK(xs.intersections.empty() == true);
        CHECK(xs.count == 0);
        
        r = ray(point(2, 0, 2), vec(0, 0, -1));
        xs = c.intersect(r);
        CHECK(xs.intersections.empty() == true);
        CHECK(xs.count == 0);
        
        r = ray(point(0, 2, 2), vec(0, -1, 0));
        xs = c.intersect(r);
        CHECK(xs.intersections.empty() == true);
        CHECK(xs.count == 0);
        
        r = ray(point(2, 2, 0), vec(-1, 0, 0));
        xs = c.intersect(r);
        CHECK(xs.intersections.empty() == true);
        CHECK(xs.count == 0);
    }

    TEST(normal_on_the_surface_of_a_cube) {
        Cube    c;

        Vec normal = c.normalAt(point(1, 0.5, -0.8));
        CHECK(normal == vec(1, 0, 0));

        normal = c.normalAt(point(-1, -0.2, 0.9));
        CHECK(normal == vec(-1, 0, 0));

        normal = c.normalAt(point(-0.4, 1, -0.1));
        CHECK(normal == vec(0, 1, 0));

        normal = c.normalAt(point(0.3, -1, -0.7));
        CHECK(normal == vec(0, -1, 0));

        normal = c.normalAt(point(-0.6, 0.3, 1));
        CHECK(normal == vec(0, 0, 1));

        normal = c.normalAt(point(0.4, 0.4, -1));
        CHECK(normal == vec(0, 0, -1));

        normal = c.normalAt(point(1, 1, 1));
        CHECK(normal == vec(1, 0, 0));

        normal = c.normalAt(point(-1, -1, -1));
        CHECK(normal == vec(-1, 0, 0));
    }
}
