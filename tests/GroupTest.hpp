#pragma once
#include <UnitTest++/UnitTest++.h>
#include "RayTracer.hpp"

SUITE(GROUP_TEST) {

    TEST(creating_new_group) {
        Group   g = Group();

        CHECK(g.getTransform() == Matrix().setIdentity());
    }

    TEST(adding_child_to_a_group) {
        Group   g = Group();
        shapePtr   s = make_unique<Sphere>();
        
        g.addChild(move(s));

        CHECK(*g[0] == Sphere());
        CHECK(g[0]->getParent() == &g);
    }

    TEST(intersecting_a_ray_with_an_empty_group) {
        Group   g = Group();

        t_ray   r = ray(point(0, 0, 0), vec(0, 0, 1));
        t_intersect xs = g.intersect(r);

        CHECK(xs.count == 0);
        CHECK(xs.intersections.empty() == true);
    }

    TEST(intersecting_a_ray_with_nonempty_group) {
        Group   g = Group();
        shapePtr  s1 = make_unique<Sphere>();
        shapePtr  s2 = make_unique<Sphere>();
        shapePtr  s3 = make_unique<Sphere>();

        s2->setTransform(translation(0, 0, -3));
        s3->setTransform(translation(5, 0, 0));
        g.addChild(move(s1));
        g.addChild(move(s2));
        g.addChild(move(s3));

        t_ray   r = ray(point(0, 0, -5), vec(0, 0, 1));
        t_intersect xs = g.intersect(r);

        CHECK(xs.count == 4);
        CHECK(xs.intersections[0].shape == g[1]);
        CHECK(xs.intersections[1].shape == g[1]);
        CHECK(xs.intersections[2].shape == g[0]);
        CHECK(xs.intersections[3].shape == g[0]);
    }

    TEST(intersecting_a_transformed_group) {
        Group   g = Group();
        shapePtr  s1 = make_unique<Sphere>();


        s1->setTransform(translation(5, 0, 0));
        g.setTransform(scaling(2, 2, 2));
        g.addChild(move(s1));


        t_ray   r = ray(point(10, 0, -10), vec(0, 0, 1));
        t_intersect xs = g.intersect(r);

        CHECK(xs.count == 2);
    }

    // TEST OF PRIVATE MEMBER
    // TEST(converting_point_from_world_to_object_space) {
    //     Group   g = Group();
    //     Group   g2 = Group();
    //     Sphere  s1 = Sphere();


    //     g.setTransform(rotationY(M_PI / 2));
    //     g2.setTransform(scaling(2, 2, 2));
    //     s1.setTransform(translation(5, 0, 0));
    //     g.addChild(&g2);
    //     g2.addChild(&s1);

    //     Point p = s1.worldToObject(point(-2, 0, -10));

    //     CHECK(p == point(0, 0, -1));
    // }

    // TEST(converting_a_normal_from_object_to_world_space) {
    //     Group   g = Group();
    //     Group   g2 = Group();
    //     Sphere  s1 = Sphere();


    //     g.setTransform(rotationY(M_PI / 2));
    //     g2.setTransform(scaling(1, 2, 3));
    //     s1.setTransform(translation(5, 0, 0));
    //     g.addChild(&g2);
    //     g2.addChild(&s1);

    //     Vec v = s1.normalToWorld(point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));

    //     CHECK(v == vec(0.2857, 0.4286, -0.8571));
    // }



}
