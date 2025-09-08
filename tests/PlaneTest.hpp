#pragma once

#include "UnitTest++/UnitTest++.h"
#include "RayTracer.hpp"

SUITE(PLANE_TEST) {

    TEST(normal_of_a_plane_is_constant_everywhere) {
        Plane p = Plane();

        Vec n1 = p.normalAt(point(0, 0, 0));
        Vec n2 = p.normalAt(point(10, 0, -10));
        Vec n3 = p.normalAt(point(-5, 0, 150));

        CHECK(n1 == vec(0, 1, 0));
        CHECK(n2 == vec(0, 1, 0));
        CHECK(n2 == vec(0, 1, 0));
    }

    TEST(intersect_with_a_ray_parallel_to_plane) {
        Plane   p = Plane();

        t_ray   r = ray(point(0, 10, 0), vec(0, 0, 1));

        t_intersect xs = p.intersect(r);
        
        CHECK(xs.count == 0);
    }

    TEST(intersect_with_a_ray_coplanar_to_plane) {
        Plane   p = Plane();

        t_ray   r = ray(point(0, 0, 0), vec(0, 0, 1));

        t_intersect xs = p.intersect(r);
        
        CHECK(xs.count == 0);
    }

    TEST(ray_intersecting_plane_from_above) {
        Plane   p = Plane();

        t_ray   r = ray(point(0, 1, 0), vec(0, -1, 0));

        t_intersect xs = p.intersect(r);
        
        CHECK(xs.count == 1);
        CHECK(*xs.intersections[0].shape == p);
    }

    TEST(ray_intersecting_plane_from_below) {
        Plane   p = Plane();

        t_ray   r = ray(point(0, -1, 0), vec(0, 1, 0));

        t_intersect xs = p.intersect(r);
        
        CHECK(xs.count == 1);
        CHECK(*xs.intersections[0].shape == p);
    }
}
