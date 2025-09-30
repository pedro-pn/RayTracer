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
        
    }
}
