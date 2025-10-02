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

    TEST(intersecting_a_ray_with_a_bounding_box_at_the_origin) {
        BoundingBox box = BoundingBox(point(-1, -1, -1), point(1, 1, 1));
        
        t_ray   r;
        
        r = ray(point(5, 0.5, 0), vec(-1, 0, 0));
        CHECK(box.intersect(r) == true);
        
        r = ray(point(-5, 0.5, 0), vec(1, 0, 0));
        CHECK(box.intersect(r) == true);
        
        r = ray(point(0.5, 5, 0) , vec(0, -1, 0));
        CHECK(box.intersect(r) == true);
        
        r = ray(point(0.5, -5, 0), vec(0, 1, 0));
        CHECK(box.intersect(r) == true);
        
        r = ray(point(0.5, 0, 5) , vec(0, 0, -1));
        CHECK(box.intersect(r) == true);
        
        r = ray(point(0.5, 0, -5), vec(0, 0, 1));
        CHECK(box.intersect(r) == true);
        
        r = ray(point(0, 0.5, 0), vec(0, 0, 1) );
        CHECK(box.intersect(r) == true);
        
        r = ray(point(-2, 0, 0), vec(2, 4, 6));
        CHECK(box.intersect(r) == false);
        
        r = ray(point(0, -2, 0), vec(6, 2, 4));
        CHECK(box.intersect(r) == false);
        
        r = ray(point(0, 0, -2), vec(4, 6, 2));
        CHECK(box.intersect(r) == false);
        
        r = ray(point(2, 0, 2), vec(0, 0, -1));
        CHECK(box.intersect(r) == false);
        
        r = ray(point(0, 2, 2), vec(0, -1, 0));
        CHECK(box.intersect(r) == false);
        
        r = ray(point(2, 2, 0), vec(-1, 0, 0));
        CHECK(box.intersect(r) == false);
    }

    TEST(intersecting_a_ray_with_a_non_cubic_bounding_box) {
        BoundingBox box = BoundingBox(point(5, -2, 0), point(11, 4, 7));
        
        t_ray   r;
        
        r = ray(point(15, 1, 2), vec(-1, 0, 0));
        CHECK(box.intersect(r) == true);
        
        r = ray(point(-5, -1, 4), vec(1, 0, 0));
        CHECK(box.intersect(r) == true);
        
        r = ray(point(7, 6, 5), vec(0, -1, 0));
        CHECK(box.intersect(r) == true);
        
        r = ray(point(9, -5, 6), vec(0, 1, 0));
        CHECK(box.intersect(r) == true);
        
        r = ray(point(8, 2, 12), vec(0, 0, -1));
        CHECK(box.intersect(r) == true);
        
        r = ray(point(6, 0, -5), vec(0, 0, 1));
        CHECK(box.intersect(r) == true);
        
        r = ray(point(8, 1, 3.5), vec(0, 0, 1));
        CHECK(box.intersect(r) == true);
        
        r = ray(point(9, -1, -8), vec(2, 4, 6));
        CHECK(box.intersect(r) == false);
        
        r = ray(point(8, 3, -4), vec(6, 2, 4));
        CHECK(box.intersect(r) == false);
        
        r = ray(point(9, -1, -2), vec(4, 6, 2));
        CHECK(box.intersect(r) == false);
        
        r = ray(point(4, 0, 9), vec(0, 0, -1));
        CHECK(box.intersect(r) == false);
        
        r = ray(point(8, 6, -1), vec(0, -1, 0));
        CHECK(box.intersect(r) == false);
        
        r = ray(point(12, 5, 4), vec(-1, 0, 0));
        CHECK(box.intersect(r) == false);
    }

    TEST(splitting_a_perfect_cube) {
        BoundingBox box = BoundingBox(point(-1, -4, -5), point(9, 6, 5));
        t_splitted_box  boxes = box.splitBounds();

        CHECK(boxes.left.getMin() == point(-1, -4, -5));
        CHECK(boxes.left.getMax() == point(4, 6, 5));
        CHECK(boxes.right.getMin() == point(4, -4, -5));
        CHECK(boxes.right.getMax() == point(9, 6, 5));
    }

    TEST(splitting_an_x_wide_box) {
        BoundingBox box = BoundingBox(point(-1, -2, -3), point(9, 5.5, 3));
        t_splitted_box  boxes = box.splitBounds();

        CHECK(boxes.left.getMin() == point(-1, -2, -3));
        CHECK(boxes.left.getMax() == point(4, 5.5, 3));
        CHECK(boxes.right.getMin() == point(4, -2, -3));
        CHECK(boxes.right.getMax() == point(9, 5.5, 3));
    }

    TEST(splitting_an_y_wide_box) {
        BoundingBox box = BoundingBox(point(-1, -2, -3), point(5, 8, 3));
        t_splitted_box  boxes = box.splitBounds();

        CHECK(boxes.left.getMin() == point(-1, -2, -3));
        CHECK(boxes.left.getMax() == point(5, 3, 3));
        CHECK(boxes.right.getMin() == point(-1, 3, -3));
        CHECK(boxes.right.getMax() == point(5, 8, 3));
    }

    TEST(splitting_an_z_wide_box) {
        BoundingBox box = BoundingBox(point(-1, -2, -3), point(5, 3, 7));
        t_splitted_box  boxes = box.splitBounds();

        CHECK(boxes.left.getMin() == point(-1, -2, -3));
        CHECK(boxes.left.getMax() == point(5, 3, 2));
        CHECK(boxes.right.getMin() == point(-1, -2, 2));
        CHECK(boxes.right.getMax() == point(5, 3, 7));
    }

    TEST(Partitioning_a_groups_children) {
        unique_ptr<Sphere> s1 = make_unique<Sphere>();
        unique_ptr<Sphere> s2 = make_unique<Sphere>();
        unique_ptr<Sphere> s3 = make_unique<Sphere>();

        Sphere *s1Ptr = &*s1;
        Sphere *s2Ptr = &*s2;
        Sphere *s3Ptr = &*s3;

        s1->setTransform(translation(-2, 0, 0));
        s2->setTransform(translation(2, 0 ,0));
        Group g = Group();

        g.addChild(move(s1));
        g.addChild(move(s2));
        g.addChild(move(s3));

        t_bucket bucket = g.partitionChildren();

        CHECK(&*bucket.left[0] == s1Ptr);
        CHECK(&*bucket.right[0] == s2Ptr);
        CHECK(&*g[0] == s3Ptr);
    }

    TEST(creating_sub_group_from_a_list_of_children) {
        unique_ptr<Sphere> s1 = make_unique<Sphere>();
        unique_ptr<Sphere> s2 = make_unique<Sphere>();
        Shape const *s1Ptr = &*s1;
        Shape *s2Ptr = &*s2;
        Group   g = Group();
        shapeList   shapes;
        shapes.push_back(move(s1));
        shapes.push_back(move(s2));
        g.makeSubgroup(shapes);

        Shape const *result1 = dynamic_cast<Shape const *>((dynamic_cast<Group const *>(g[0]))->operator[](0));
        Shape const *result2 = dynamic_cast<Shape const *>((dynamic_cast<Group const *>(g[0]))->operator[](1));
        CHECK(g.count() == 1);
        CHECK(result1 == s1Ptr);
        CHECK(result2 == s2Ptr);
    }

    TEST(subdividing_a_primitive_does_nothing) {
        Sphere s = Sphere();

        s.divide();

        CHECK(s == s);
    }

    TEST(subdividing_a_group_partitions_its_children) {
        unique_ptr<Sphere> s1 = make_unique<Sphere>();
        unique_ptr<Sphere> s2 = make_unique<Sphere>();
        unique_ptr<Sphere> s3 = make_unique<Sphere>();

        Shape const *s1Ptr = s1.get();
        Shape const *s2Ptr = s2.get();
        Shape const *s3Ptr = s3.get();
        s1->setTransform(translation(-2, -2, 0));
        s2->setTransform(translation(-2, 2, 0));
        s3->setTransform(scaling(4, 4, 4));

        Group g = Group();
        g.addChild(move(s1));
        g.addChild(move(s2));
        g.addChild(move(s3));
        g.divide(1);

        CHECK(g[0] == s3Ptr);
        Group const *subgroup1 = dynamic_cast<Group const *>(g[1]);
        Group const *g2 = dynamic_cast<Group const *>(subgroup1->operator[](0));
        Group const *g3 = dynamic_cast<Group const *>(subgroup1->operator[](1));
        CHECK(subgroup1->count() == 2);
        CHECK(g2->operator[](0) == s1Ptr);
        CHECK(g3->operator[](0) == s2Ptr);
    }

    TEST(subdividing_a_group_with_too_few_children) {
        unique_ptr<Sphere> s1 = make_unique<Sphere>();
        unique_ptr<Sphere> s2 = make_unique<Sphere>();
        unique_ptr<Sphere> s3 = make_unique<Sphere>();
        unique_ptr<Sphere> s4 = make_unique<Sphere>();

        Shape const *s1Ptr = s1.get();
        Shape const *s2Ptr = s2.get();
        Shape const *s3Ptr = s3.get();
        Shape const *s4Ptr = s4.get();

        s1->setTransform(translation(-2, 0, 0));
        s2->setTransform(translation(2, 1, 0));
        s3->setTransform(translation(2, -1, 0));

        groupPtr  subGroup = make_unique<Group>();
        Group const *subGroupPtr = subGroup.get();

        subGroup->addChild(move(s1));
        subGroup->addChild(move(s2));
        subGroup->addChild(move(s3));

        Group g = Group();
        g.addChild(move(subGroup));
        g.addChild(move(s4));

        g.divide(3);

        CHECK(g[0] == subGroupPtr);
        CHECK(g[1] == s4Ptr);

        Group  const *sub = dynamic_cast<Group const *>(g[0]);

        CHECK(sub->count() == 2);
        Group const *subsub1 = dynamic_cast<Group const *>(sub->operator[](0));
        CHECK(subsub1->operator[](0) == s1Ptr);

        Group const *subsub2 = dynamic_cast<Group const *>(sub->operator[](1));
        CHECK(subsub2->operator[](0) == s2Ptr);
        CHECK(subsub2->operator[](1) == s3Ptr);
    }
}
