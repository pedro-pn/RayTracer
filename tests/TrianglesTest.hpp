#pragma once

#include <UnitTest++/UnitTest++.h>
#include "RayTracer.hpp"

SUITE(TRIANGLE_SUITE) {

    TEST(constructing_a_triangle) {
        Triangle t = Triangle(point(0, 1, 0), point(-1, 0, 0), point(1, 0, 0));

        CHECK(t.p1() == point(0, 1, 0));
        CHECK(t.p2() == point(-1, 0, 0));
        CHECK(t.p3() == point(1, 0, 0));
        CHECK(t.e1() == vec(-1, -1, 0));
        CHECK(t.e2() == vec(1, -1, 0));
        CHECK(t.normal() == vec(0, 0, -1));
    }

    TEST(finding_the_normal_on_a_triangle) {
        Triangle t = Triangle();

        Vec n1 = t.normalAt(point(0, 0.5, 0));
        Vec n2 = t.normalAt(point(-0.5, 0.75, 0));
        Vec n3 = t.normalAt(point(0.5, 0.25, 0));

        CHECK(n1 == t.normal());
        CHECK(n2 == t.normal());
        CHECK(n3 == t.normal());
    }

    TEST(intersecting_a_ray_parallel_to_the_triangle) {
        Triangle t = Triangle();

        t_ray r = ray(point(0, -1, -2), vec(0, 1, 0));

        t_intersect xs = t.intersect(r);

        CHECK(xs.count == 0);
        CHECK(xs.intersections.empty());
    }

    TEST(ray_misses_p1_p3_edge) {
        Triangle t = Triangle();

        t_ray r = ray(point(1, 1, -2), vec(0, 0, 1));
        t_intersect xs = t.intersect(r);

        CHECK(xs.count == 0);
        CHECK(xs.intersections.empty());
    }

    TEST(ray_misses_p1_p2_edge) {
        Triangle t = Triangle();

        t_ray r = ray(point(-1, 1, -2), vec(0, 0, 1));
        t_intersect xs = t.intersect(r);

        CHECK(xs.count == 0);
        CHECK(xs.intersections.empty());
    }

    TEST(ray_misses_p2_p3_edge) {
        Triangle t = Triangle();

        t_ray r = ray(point(0, -1, -2), vec(0, 0, 1));
        t_intersect xs = t.intersect(r);

        CHECK(xs.count == 0);
        CHECK(xs.intersections.empty());
    }

    TEST(ray_strikes_a_triangle) {
        Triangle t = Triangle();

        t_ray r = ray(point(0, 0.5, -2), vec(0, 0, 1));
        t_intersect xs = t.intersect(r);

        CHECK(xs.count == 1);
        CHECK(xs.intersections[0].t == 2);
    }
}
