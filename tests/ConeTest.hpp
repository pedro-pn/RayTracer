#pragma once
#include <UnitTest++/UnitTest++.h>
#include "RayTracer.hpp"
#include <iomanip>

SUITE(CONE_SUITE) {

    TEST(intersecting_cone_with_a_ray) {
        Cone   c = Cone();

        t_intersect xs;
        t_ray r = ray(point(0, 0, -5), vec(0, 0, 1).normalize());
        xs = c.intersect(r);
        CHECK(xs.count == 2);
        CHECK(areEqual(xs.intersections[0].t, 5));
        CHECK(areEqual(xs.intersections[1].t, 5));

        r = ray(point(0, 0, -5), vec(1, 1, 1).normalize());
        xs = c.intersect(r);
        CHECK(xs.count == 2);
        CHECK(areEqual(xs.intersections[0].t, 8.66025));
        CHECK(areEqual(xs.intersections[1].t, 8.66025));

        r = ray(point(1, 1, -5), vec(-0.5, -1, 1).normalize());
        xs = c.intersect(r);
        CHECK(xs.count == 2);
        CHECK(areEqual(xs.intersections[0].t, 4.55006));
        CHECK(areEqual(xs.intersections[1].t, 49.44994));
    }

    TEST(intersecting_a_cone_with_a_ray_parallel_to_one_of_its_halves) {
        Cone   c = Cone();

        t_intersect xs;
        t_ray r = ray(point(0, 0, -1), vec(0, 1, 1).normalize());
        xs = c.intersect(r);
        CHECK(xs.count == 1);
        CHECK(areEqual(xs.intersections[0].t, 0.35355));
    }

    TEST(intersecting_cone_end_cap) {
        Cone    c = Cone();
        c.setMinimum(-0.5);
        c.setMaximum(0.5);
        c.closed();

        t_intersect xs;
        t_ray   r = ray(point(0, 0, -5), vec(0, 1, 0));
        xs = c.intersect(r);
        CHECK(xs.count == 0);

        r = ray(point(0, 0, -0.25), vec(0, 1, 1).normalize());
        xs = c.intersect(r);
        CHECK(xs.count == 2);

        r = ray(point(0, 0, -0.25), vec(0, 1, 0).normalize());
        xs = c.intersect(r);
        CHECK(xs.count == 4);
    }

    TEST(computing_normal_vector_on_a_cone) {
        Cone    cc = Cone();
        
        CHECK(cc.normalAt(point(0, 0, 0)) == vec(0, 0, 0));
        CHECK(cc.normalAt(point(1, 1, 1)) == vec(0.5, -0.70711, 0.5));
        CHECK(cc.normalAt(point(-1, -1, 0)) == vec(-0.70711, 0.70711, 0));
    }
}
