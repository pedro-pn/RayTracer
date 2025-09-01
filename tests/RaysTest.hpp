#ifndef RAYSTESTS_HPP
# define RAYSTESTS_HPP

# include <UnitTest++/UnitTest++.h>
# include "TestUtils.hpp"
# include "RayTracer.hpp"

SUITE(CREATING_RAYS) {
    
    TEST(creating_rays) {
        Point   origin = point(1, 2, 3);
        Vec     direction = vec(4, 5, 6);

        t_ray     r = ray(origin, direction);

        CHECK(r.origin == origin);
        CHECK(r.direction == direction);
    }

    TEST(computing_point_from_distance) {
        t_ray   r = ray(point(2, 3, 4), vec(1, 0, 0));

        CHECK(position(r, 0) == point(2, 3, 4));
        CHECK(position(r, 1) == point(3, 3, 4));
        CHECK(position(r, -1) == point(1, 3, 4));
        CHECK(position(r, 2.5) == point(4.5, 3, 4));
    }

    TEST(ray_intersects_with_sphere) {
        t_ray   r = ray(point(0, 0, -5), vec(0, 0, 1));
        Sphere  *s = new Sphere();

        t_intersect xs = intersect(s, r);

        CHECK(xs.count == 2);
        CHECK(xs.intersections[0].t == 4.0);
        CHECK(xs.intersections[1].t == 6.0);

        delete s;
    }

    TEST(ray_intersect_a_sphere_tangent) {
        t_ray   r = ray(point(0, 1, -5), vec(0, 0, 1));
        Sphere  *s = new Sphere();

        t_intersect xs = intersect(s, r);

        CHECK(xs.count == 2);
        CHECK(xs.intersections[0].t == 5.0);
        CHECK(xs.intersections[1].t == 5.0);

        delete s;
    }

    TEST(ray_misses_sphere) {
        t_ray   r = ray(point(0, 2, -5), vec(0, 0, 1));
        Sphere  *s = new Sphere();

        t_intersect xs = intersect(s, r);

        CHECK(xs.count == 0);

        delete s;
    }
    
    TEST(ray_originates_inside_sphere) {
        t_ray   r = ray(point(0, 0, 0), vec(0, 0, 1));
        Sphere  *s = new Sphere();

        t_intersect xs = intersect(s, r);

        CHECK(xs.count == 2);
        CHECK(xs.intersections[0].t == -1.0);
        CHECK(xs.intersections[1].t== 1.0);

        delete s;
    }

    TEST(ray_originates_behind_sphere) {
        t_ray   r = ray(point(0, 0, 5), vec(0, 0, 1));
        Sphere  *s = new Sphere();

        t_intersect xs = intersect(s, r);

        CHECK(xs.count == 2);
        CHECK(xs.intersections[0].t == -6.0);
        CHECK(xs.intersections[1].t == -4.0);

        delete s;
    }

    TEST(intersection_encapsulates_t_and_object) {
        Sphere  *s = new Sphere();
        t_intersection i = intersection(3.5, s);

        CHECK(i.t == 3.5);
        CHECK(i.object == s);

        delete s;
    }

    TEST(intersect_sets_object_on_intersection) {
        Sphere  *s = new Sphere();
        t_ray     r = ray(point(0, 0, -5), vec(0,0,1));

        auto xs = intersect(s, r);

        CHECK(xs.count == 2);
        CHECK(xs.intersections[0].object == s);
        CHECK(xs.intersections[1].object == s);

        delete s;
    }

    TEST(hit_when_all_t_are_positive) {
        Sphere  *s = new Sphere();
        t_intersection  i1{1, s};
        t_intersection  i2{2, s};

        t_intersect xs;

        xs.count = 2;
        xs.intersections.push_back(i1);
        xs.intersections.push_back(i2);
        auto  i = hit(xs);

        CHECK(i == i1);
    }

    TEST(hit_when_some_t_are_negative) {
        Sphere  *s = new Sphere();
        t_intersection  i1{-1, s};
        t_intersection  i2{1, s};

        t_intersect xs;

        xs.count = 2;
        xs.intersections.push_back(i1);
        xs.intersections.push_back(i2);
        auto  i = hit(xs);

        CHECK(i == i2);
    }

    TEST(hit_when_all_t_are_negative) {
        Sphere  *s = new Sphere();
        t_intersection  i1{-2, s};
        t_intersection  i2{-1, s};

        t_intersect xs;

        xs.count = 2;
        xs.intersections.push_back(i1);
        xs.intersections.push_back(i2);
        auto  i = hit(xs);

        CHECK(i == nullopt);
    }

    TEST(hit_is_always_the_lowest_negative_value) {
        Sphere  *s = new Sphere();
        t_intersection  i1{5, s};
        t_intersection  i2{7, s};
        t_intersection  i3{-3, s};
        t_intersection  i4{2, s};

        t_intersect xs;

        xs.count = 2;
        xs.intersections.push_back(i1);
        xs.intersections.push_back(i2);
        xs.intersections.push_back(i3);
        xs.intersections.push_back(i4);
        auto  i = hit(xs);

        CHECK(i == i4);
    }

    TEST(translating_a_ray) {
        t_ray   r = ray(point(1, 2, 3), vec(0, 1, 0));
        Matrix  m = translation(3, 4, 5);

        t_ray   r2 = transformRay(r, m);

        CHECK(r.origin == point(1, 2, 3));
        CHECK(r.direction == vec(0, 1, 0));
        CHECK(r2.origin == point(4, 6, 8));
        CHECK(r2.direction == vec(0, 1, 0));
    }

    TEST(scaling_a_ray) {
        t_ray   r = ray(point(1, 2, 3), vec(0, 1, 0));
        Matrix  m = scaling(2, 3, 4);

        t_ray   r2 = transformRay(r, m);

        CHECK(r.origin == point(1, 2, 3));
        CHECK(r.direction == vec(0, 1, 0));
        CHECK(r2.origin == point(2, 6, 12));
        CHECK(r2.direction == vec(0, 3, 0));
    }

    TEST(sphere_has_transformation_matrix) {
        Sphere  *s = new Sphere();
 
        CHECK(s->getTransform() == Matrix().setIdentity());

        delete s;
    }

    TEST(changing_spheres_transformation) {
        Sphere  *s = new Sphere();
        Matrix  t = translation(2, 3, 4);

        s->setTransform(t);

        CHECK(s->getTransform() == t);

        delete s;
    }

    TEST(intersecting_scaled_sphere_with_a_ray) {
        t_ray   r = ray(point(0, 0, -5), vec(0, 0, 1));
        Sphere  *s = new Sphere();

        s->setTransform(scaling(2, 2, 2));

        t_intersect xs = intersect(s, r);

        CHECK(xs.count == 2);
        CHECK(xs.intersections[0].t == 3);
        CHECK(xs.intersections[1].t == 7);

        delete s;
    }

    TEST(intersecting_translated_sphere_whti_ray) {
        t_ray   r = ray(point(0, 0, -5), vec(0, 0, 1));
        Sphere  *s = new Sphere();

        s->setTransform(translation(5, 0, 0));

        t_intersect xs = intersect(s, r);

        CHECK(xs.count == 0);

        delete s;
    }

}

#endif /* RAYSTESTS_HPP */
