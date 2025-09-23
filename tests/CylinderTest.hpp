#pragma once
#include <UnitTest++/UnitTest++.h>
#include "RayTracer.hpp"

SUITE(CYLINDER_SUITE) {
    
    TEST(ray_misses_a_cylinder) {
        Cylinder cyl = Cylinder();
        
        t_ray   r = ray(point(1, 0, 0), vec(0, 1, 0));
        t_intersect xs = cyl.intersect(r);
        CHECK(xs.count == 0);
        CHECK(xs.intersections.empty() == true);

        r = ray(point(0, 0, 0), vec(0, 1, 0));
        xs = cyl.intersect(r);
        CHECK(xs.count == 0);
        CHECK(xs.intersections.empty() == true);

        r = ray(point(0, 0, -5), vec(1, 1, 1).normalize());
        xs = cyl.intersect(r);
        CHECK(xs.count == 0);
        CHECK(xs.intersections.empty() == true);
    }
    
    TEST(ray_intersects_a_cylinder) {
        Cylinder cyl = Cylinder();
        
        t_ray   r = ray(point(1, 0, -5), vec(0, 0, 1));
        t_intersect xs = cyl.intersect(r);
        CHECK(xs.count == 2);
        CHECK(xs.intersections[0].t == 5);
        CHECK(xs.intersections[1].t == 5);
        
        r = ray(point(0, 0, -5), vec(0, 0, 1));
        xs = cyl.intersect(r);
        CHECK(xs.count == 2);
        CHECK(xs.intersections[0].t == 4);
        CHECK(xs.intersections[1].t == 6);
        
        r = ray(point(0.5, 0, -5), vec(0.1, 1, 1).normalize());
        xs = cyl.intersect(r);
        CHECK(xs.count == 2);
        CHECK(areEqual(xs.intersections[0].t, 6.80798));
        CHECK(areEqual(xs.intersections[1].t, 7.08872));
    }

    TEST(normal_vector_on_a_cylinder) {
        Cylinder    cyl = Cylinder();

        CHECK(cyl.normalAt(point(1, 0, 0)) == vec(1, 0, 0));
        CHECK(cyl.normalAt(point(0, 5, -1)) == vec(0, 0, -1));
        CHECK(cyl.normalAt(point(0, -2, 1)) == vec(0, 0, 1));
        CHECK(cyl.normalAt(point(-1, 1, 0)) == vec(-1, 0, 0));
    }

    TEST(default_minimum_and_maximum_for_a_cylinder) {
        Cylinder    cyl = Cylinder();

        CHECK(areEqual(cyl.getMinimum(), -INFINITY));
        CHECK(areEqual(cyl.getMaximum(), INFINITY));
    }

    TEST(intersecting_constrained_cylinder) {
        Cylinder    cyl = Cylinder();

        cyl.setMinimum(1);
        cyl.setMaximum(2);

        t_ray r = ray(point(0, 1.5, 0), vec(0.1, 1, 0).normalize());
        t_intersect xs = cyl.intersect(r);
        CHECK(xs.count == 0);

        r = ray(point(0, 3, -5), vec(0, 0, 1).normalize());
        xs = cyl.intersect(r);
        CHECK(xs.count == 0);

        r = ray(point(0, 0, -5), vec(0, 0, 1).normalize());
        xs = cyl.intersect(r);
        CHECK(xs.count == 0);

        r = ray(point(0, 2, -5), vec(0, 0, 1).normalize());
        xs = cyl.intersect(r);
        CHECK(xs.count == 0);

        r = ray(point(0, 1, -5), vec(0, 0, 1).normalize());
        xs = cyl.intersect(r);
        CHECK(xs.count == 0);

        r = ray(point(0, 1.5, -2), vec(0, 0, 1).normalize());
        xs = cyl.intersect(r);
        CHECK(xs.count == 2);
    }
    
    TEST(default_closed_value_for_a_cylinder) {
        Cylinder    cyl = Cylinder();
        
        CHECK(cyl.isClosed() == false);
    }

    TEST(intersecting_the_caps_of_a_closed_cylinder) {
        Cylinder    cyl = Cylinder();

        cyl.setMinimum(1);
        cyl.setMaximum(2);
        cyl.closed();

        t_ray r = ray(point(0, 3, 0), vec(0, -1, 0).normalize());
        t_intersect xs = cyl.intersect(r);
        CHECK(xs.count == 2);

        r = ray(point(0, 3, -2), vec(0, -1, 2).normalize());
        xs = cyl.intersect(r);
        CHECK(xs.count == 2);

        r = ray(point(0, 4, -2), vec(0, -1, 1).normalize());
        xs = cyl.intersect(r);
        CHECK(xs.count == 2);

        r = ray(point(0, 0, -2), vec(0, 1, 2).normalize());
        xs = cyl.intersect(r);
        CHECK(xs.count == 2);

        r = ray(point(0, -1, -2), vec(0, 1, 1).normalize());
        xs = cyl.intersect(r);
        CHECK(xs.count == 2);
    }

    TEST(normal_vector_on_a_cylinder_end_caps) {
        Cylinder    cyl = Cylinder();

        cyl.setMinimum(1);
        cyl.setMaximum(2);
        cyl.closed();

        CHECK(cyl.normalAt(point(0, 1, 0)) == vec(0, -1, 0));
        CHECK(cyl.normalAt(point(0.5, 1, 0)) == vec(0, -1, 0));
        CHECK(cyl.normalAt(point(0, 1, 0.5)) == vec(0, -1, 0));
        CHECK(cyl.normalAt(point(0, 2, 0)) == vec(0, 1, 0));
        CHECK(cyl.normalAt(point(0.5, 2, 0)) == vec(0, 1, 0));
        CHECK(cyl.normalAt(point(0, 2, 0.5)) == vec(0, 1, 0));
    }
}
