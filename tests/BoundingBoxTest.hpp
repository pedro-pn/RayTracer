#pragma once

#include <UnitTest++/UnitTest++.h>
#include "RayTracer.hpp"

SUITE(BOUNDING_BOX_SUITE) {

    TEST(creating_an_empty_bounding_box) {
        BoundingBox box = BoundingBox();

        CHECK(box.getMin() == point(INFINITY, INFINITY, INFINITY));
        CHECK(box.getMax() == point(-INFINITY, -INFINITY, -INFINITY));
    }
    
    TEST(creating_a_bounding_box_with_volume) {
        BoundingBox box = BoundingBox(point(-1, -2, -3), point(3, 2, 1));
        
        CHECK(box.getMin() == point(-1, -2, -3));
        CHECK(box.getMax() == point(3, 2, 1));
    }
    
    TEST(adding_points_to_an_empty_bounding_box) {
        BoundingBox box = BoundingBox();
        
        box.addPoint(point(-5, 2, 0));
        box.addPoint(point(7, 0, -3));
        
        CHECK(box.getMin() == point(-5, 0, -3));
        CHECK(box.getMax() == point(7, 2, 0));
    }

    TEST(sphere_bounding_box) {
        Sphere  s = Sphere();

        BoundingBox  box = s.boundsOf();

        CHECK(box.getMin() == point(-1, -1, -1));
        CHECK(box.getMax() == point(1, 1, 1));
    }

    TEST(plane_bounding_box) {
        Plane   p = Plane();

        BoundingBox  box = p.boundsOf();

        CHECK(box.getMin() == point(-INFINITY, 0, -INFINITY));
        CHECK(box.getMax() == point(INFINITY, 0, INFINITY));
    }

    TEST(cube_bounding_box) {
        Cube   c = Cube();

        BoundingBox  box = c.boundsOf();

        CHECK(box.getMin() == point(-1, -1, -1));
        CHECK(box.getMax() == point(1, 1, 1));
    }

    TEST(cylinder_bounding_box) {
        Cylinder   cy = Cylinder();

        BoundingBox  box = cy.boundsOf();

        CHECK(box.getMin() == point(-1, -INFINITY, -1));
        CHECK(box.getMax() == point(1, INFINITY, 1));
    }

    TEST(bounded_cylinder_bounding_box) {
        Cylinder   cy = Cylinder();
        cy.setMinimum(-5);
        cy.setMaximum(3);
        BoundingBox  box = cy.boundsOf();

        CHECK(box.getMin() == point(-1, -5, -1));
        CHECK(box.getMax() == point(1, 3, 1));
    }

    TEST(cone_bounding_box) {
        Cone   c = Cone();

        BoundingBox  box = c.boundsOf();

        CHECK(box.getMin() == point(-INFINITY, -INFINITY, -INFINITY));
        CHECK(box.getMax() == point(INFINITY, INFINITY, INFINITY));
    }

    TEST(bounded_cone_bounding_box) {
        Cone   c = Cone();
        c.setMinimum(-5);
        c.setMaximum(3);
        BoundingBox  box = c.boundsOf();

        CHECK(box.getMin() == point(-5, -5, -5));
        CHECK(box.getMax() == point(5, 3, 5));
    }

    TEST(adding_one_bounding_box_to_another) {
        BoundingBox box1 = BoundingBox(point(-5, -2, 0), point(7, 4, 4));
        BoundingBox box2 = BoundingBox(point(8, -7, -2), point(14, 2, 8));

        box1.addBox(box2);
        BoundingBox box3 = box1 + box2;

        CHECK(box1.getMin() == point(-5, -7, -2));
        CHECK(box1.getMax() == point(14, 4, 8));
    }

    TEST(checking_if_a_box_contains_a_given_point) {
        BoundingBox box = BoundingBox(point(5, -2, 0), point(11, 4, 7));
        Point p;

        p = point(5, -2, 0);
        CHECK(box.containsPoint(p) == true);

        p = point(11, 4, 7);
        CHECK(box.containsPoint(p) == true);

        p = point(8, 1, 3);
        CHECK(box.containsPoint(p) == true);

        p = point(3, 0, 3);
        CHECK(box.containsPoint(p) == false);

        p = point(8, -4, 3);
        CHECK(box.containsPoint(p) == false);

        p = point(8, 1, -1);
        CHECK(box.containsPoint(p) == false);

        p = point(13, 1, 3);
        CHECK(box.containsPoint(p) == false);

        p = point(8, 5, 3);
        CHECK(box.containsPoint(p) == false);

        p = point(8, 1, 8);
        CHECK(box.containsPoint(p) == false);
    }

    TEST(checking_if_a_box_contains_a_given_box) {
        BoundingBox box1 = BoundingBox(point(5, -2, 0), point(11, 4, 7));
        BoundingBox box2;

        box2 = BoundingBox(point(5, -2, 0), point(11, 4, 7));
        CHECK(box1.containsBox(box2) == true);

        box2 = BoundingBox(point(6, -1, 1), point(10, 3, 6));
        CHECK(box1.containsBox(box2) == true);

        box2 = BoundingBox(point(4, -3, -1), point(10, 3, 6));
        CHECK(box1.containsBox(box2) == false);

        box2 = BoundingBox(point(6, -1, 1), point(12, 5, 8));
        CHECK(box1.containsBox(box2) == false);
    }

    TEST(tranforming_a_bounding_box) {
        BoundingBox box = BoundingBox(point(-1, -1, -1), point(1, 1, 1));
        BoundingBox box2 = box.transform(rotationX(M_PI / 4) * rotationY(M_PI / 4));

        CHECK(box2.getMin() == point(-1.4142, -1.7071, -1.7071));
        CHECK(box2.getMax() == point(1.4142, 1.7071, 1.7071));
    }

    TEST(querying_a_shapes_bounding_box_in_its_parents_space) {
        Sphere s = Sphere();
        s.setTransform(translation(1, -3, 5) * scaling(0.5, 2 ,4));
        BoundingBox box = s.parentSpaceBoundsOf();

        CHECK(box.getMin() == point(0.5, -5, 1));
        CHECK(box.getMax() == point(1.5, -1, 9));
    }

    TEST(group_has_a_bounding_box_that_contains_its_children) {
        shapePtr  s = make_unique<Sphere>();
        s->setTransform(translation(2, 5, -3) * scaling(2, 2, 2));
        shapePtr cy = make_unique<Cylinder>();
        dynamic_cast<Cylinder *>(&*cy)->setMaximum(2);
        dynamic_cast<Cylinder *>(&*cy)->setMinimum(-2);
        cy->setTransform(translation(-4, -1, 4) * scaling(0.5, 1, 0.5));

        Group   g = Group();
        g.addChild(move(s));
        g.addChild(move(cy));

        BoundingBox box = g.boundsOf();

        CHECK(box.getMin() == point(-4.5, -3, -5));
        CHECK(box.getMax() == point(4, 7, 4.5));
    }
}
