#pragma once

#include <UnitTest++/UnitTest++.h>
#include "TestUtils.hpp"
#include "RayTracer.hpp"

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
        Sphere  s =  Sphere();

        t_intersect xs = s.intersect(r);

        CHECK(xs.count == 2);
        CHECK(xs.intersections[0].t == 4.0);
        CHECK(xs.intersections[1].t == 6.0);

    }

    TEST(ray_intersect_a_sphere_tangent) {
        t_ray   r = ray(point(0, 1, -5), vec(0, 0, 1));
        Sphere  s = Sphere();

        t_intersect xs = s.intersect(r);

        CHECK(xs.count == 2);
        CHECK(xs.intersections[0].t == 5.0);
        CHECK(xs.intersections[1].t == 5.0);

    }

    TEST(ray_misses_sphere) {
        t_ray   r = ray(point(0, 2, -5), vec(0, 0, 1));
        Sphere  s = Sphere();

        t_intersect xs = s.intersect(r);

        CHECK(xs.count == 0);
    }
    
    TEST(ray_originates_inside_sphere) {
        t_ray   r = ray(point(0, 0, 0), vec(0, 0, 1));
        Sphere  s = Sphere();

        t_intersect xs = s.intersect(r);

        CHECK(xs.count == 2);
        CHECK(xs.intersections[0].t == -1.0);
        CHECK(xs.intersections[1].t== 1.0);
    }

    TEST(ray_originates_behind_sphere) {
        t_ray   r = ray(point(0, 0, 5), vec(0, 0, 1));
        Sphere  s = Sphere();

        t_intersect xs = s.intersect(r);

        CHECK(xs.count == 2);
        CHECK(xs.intersections[0].t == -6.0);
        CHECK(xs.intersections[1].t == -4.0);

    }

    TEST(intersection_encapsulates_t_and_object) {
        Sphere  s = Sphere();
        t_intersection i = intersection(3.5, s);

        CHECK(i.t == 3.5);
        CHECK(*i.shape == s);
    }

    TEST(intersect_sets_object_on_intersection) {
        Sphere    s = Sphere();
        t_ray     r = ray(point(0, 0, -5), vec(0,0,1));

        auto xs = s.intersect(r);

        CHECK(xs.count == 2);
        CHECK(*xs.intersections[0].shape == s);
        CHECK(*xs.intersections[1].shape == s);

    }

    TEST(hit_when_all_t_are_positive) {
        Sphere  s = Sphere();
        t_intersection  i1{1, &s};
        t_intersection  i2{2, &s};

        t_intersect xs;

        xs.count = 2;
        xs.intersections.push_back(i1);
        xs.intersections.push_back(i2);
        auto  i = hit(xs);

        CHECK(i == i1);
    }

    TEST(hit_when_some_t_are_negative) {
        Sphere  s = Sphere();
        t_intersection  i1{-1, &s};
        t_intersection  i2{1, &s};

        t_intersect xs;

        xs.count = 2;
        xs.intersections.push_back(i1);
        xs.intersections.push_back(i2);
        auto  i = hit(xs);

        CHECK(i == i2);
    }

    TEST(hit_when_all_t_are_negative) {
        Sphere  s = Sphere();
        t_intersection  i1{-2, &s};
        t_intersection  i2{-1, &s};

        t_intersect xs;

        xs.count = 2;
        xs.intersections.push_back(i1);
        xs.intersections.push_back(i2);
        auto  i = hit(xs);

        CHECK(i == nullopt);
    }

    TEST(hit_is_always_the_lowest_negative_value) {
        Sphere  s = Sphere();
        t_intersection  i1{5, &s};
        t_intersection  i2{7, &s};
        t_intersection  i3{-3, &s};
        t_intersection  i4{2, &s};

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
        Sphere  s = Sphere();
 
        CHECK(s.getTransform() == Matrix().setIdentity());

    }

    TEST(changing_spheres_transformation) {
        Sphere  s = Sphere();
        Matrix  t = translation(2, 3, 4);

        s.setTransform(t);

        CHECK(s.getTransform() == t);
    }

    TEST(intersecting_scaled_sphere_with_a_ray) {
        t_ray   r = ray(point(0, 0, -5), vec(0, 0, 1));
        Sphere  s = Sphere();

        s.setTransform(scaling(2, 2, 2));

        t_intersect xs = s.intersect(r);

        CHECK(xs.count == 2);
        CHECK(xs.intersections[0].t == 3);
        CHECK(xs.intersections[1].t == 7);
    }

    TEST(intersecting_translated_sphere_whti_ray) {
        t_ray   r = ray(point(0, 0, -5), vec(0, 0, 1));
        Sphere  s = Sphere();

        s.setTransform(translation(5, 0, 0));

        t_intersect xs = s.intersect(r);

        CHECK(xs.count == 0);
    }

    TEST(normal_on_a_sphere_at_point_on_x_axis) {
        Sphere  s = Sphere();
        
        Vec     n = s.normalAt(point(1, 0 ,0));

        CHECK(n == vec(1, 0, 0));
    }

    TEST(normal_on_a_phere_at_point_on_y_axis) {
        Sphere  s = Sphere();
        
        Vec     n = s.normalAt(point(0, 1 ,0));

        CHECK(n == vec(0, 1, 0));

    }

    TEST(normal_on_a_phere_at_point_on_z_axis) {
        Sphere  s = Sphere();
        
        Vec     n = s.normalAt(point(0, 0 ,1));

        CHECK(n == vec(0, 0, 1));
    }

    TEST(normal_on_a_phere_at_non_axial_point) {
        Sphere  s = Sphere();
        
        Vec     n = s.normalAt(point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));

        CHECK(n == vec(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));

    }

    TEST(normal_is_a_normalize_vector) {
        Sphere  s = Sphere();
        
        Vec     n = s.normalAt(point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));

        CHECK(n == n.normalize());
    }

    TEST(computing_normal_on_a_translated_sphere) {
        Sphere  s = Sphere();
        s.setTransform(Matrix().setIdentity().translate(0, 1, 0));
        Vec     n = s.normalAt(point(0, 1.70711, -0.70711));

        CHECK(n == vec(0, 0.70711, -0.70711));
    }

    TEST(computing_normal_on_a_transformed_sphere) {
        Sphere  s = Sphere();
        s.setTransform(Matrix().setIdentity().rotateZ(M_PI / 5).scale(1, 0.5, 1));
        Vec     n = s.normalAt(point(0, sqrt(2) / 2, -sqrt(2) / 2));

        CHECK(n == vec(0, 0.97014, -0.24254));
    }

    TEST(reflecting_a_vector_approaching_at_45) {
        Vec v = vec(1, -1, 0);
        Vec n = vec(0, 1, 0);
        Vec reflected = reflect(v, n);

        CHECK(reflected == vec(1, 1, 0));
    }

    TEST(reflecting_a_vector_off_slanted_surface) {
        Vec v = vec(0, -1, 0);
        Vec n = vec(sqrt(2) / 2, sqrt(2) / 2, 0);
        Vec reflected = reflect(v, n);

        CHECK(reflected == vec(1, 0, 0));
    }

    TEST(point_light_has_position_and_intensity) {
        Color   intensity = color(1, 1, 1);
        Point   position = point(0, 0, 0);
        t_light   light = pointLight(position, intensity);

        CHECK(light.position == position);
        CHECK(light.intensity == intensity);
    }

    TEST(default_material) {
        t_material m = t_material();

        CHECK(m.ambient == 0.1);
        CHECK(m.colour == color(1, 1, 1));
        CHECK(m.diffuse == 0.9);
        CHECK(m.specular == 0.9);
        CHECK(m.shininess == 200.0);
    }

    TEST(sphere_has_material) {
        Sphere  *s = new Sphere();
        
        CHECK(s->getMaterial() == t_material());
        delete s;
    }

    TEST(sphere_may_be_assigned_material) {
        Sphere  *s = new Sphere();
        t_material m =  t_material();
        m.ambient = 1;
        s->setMaterial(m);

        CHECK(s->getMaterial().ambient == m.ambient);

        delete s;
    }

    TEST(lighting_with_eye_between_light_and_surface) {
        t_material  m = t_material();
        Point   position = point(0, 0, 0);
        Vec     eyev = vec(0, 0, -1);
        Vec     normalv = vec(0, 0, -1);
        t_light light = pointLight(point(0, 0, -10), color(1, 1, 1));

        Color   result = lighting(m, light, position, eyev, normalv, false);

        CHECK(result == color(1.9, 1.9, 1.9));
    }

    TEST(lighting_with_eye_between_light_and_surface_eye_offset_45) {
        t_material  m = t_material();
        Point   position = point(0, 0, 0);
        Vec     eyev = vec(0, sqrt(2) / 2, -sqrt(2) / 2);
        Vec     normalv = vec(0, 0, -1);
        t_light light = pointLight(point(0, 0, -10), color(1, 1, 1));

        Color   result = lighting(m, light, position, eyev, normalv, false);

        CHECK(result == color(1.0, 1.0, 1.0));
    }

    TEST(lighting_with_eye_opposite__surface_light_offset_45) {
        t_material  m = t_material();
        Point   position = point(0, 0, 0);
        Vec     eyev = vec(0, 0, -1);
        Vec     normalv = vec(0, 0, -1);
        t_light light = pointLight(point(0, 10, -10), color(1, 1, 1));

        Color   result = lighting(m, light, position, eyev, normalv, false);

        CHECK(result == color(0.7364, 0.7364, 0.7364));
    }

    TEST(lighting_with_eye_in_the_path_of_reflection_vector) {
        t_material  m = t_material();
        Point   position = point(0, 0, 0);
        Vec     eyev = vec(0, -sqrt(2) / 2 , -sqrt(2) / 2);
        Vec     normalv = vec(0, 0, -1);
        t_light light = pointLight(point(0, 10, -10), color(1, 1, 1));

        Color   result = lighting(m, light, position, eyev, normalv, false);

        CHECK(result == color(1.6364, 1.6364, 1.6364));
    }

    TEST(lighting_with_eye_behing_the_surface) {
        t_material  m = t_material();
        Point   position = point(0, 0, 0);
        Vec     eyev = vec(0, 0, -1);
        Vec     normalv = vec(0, 0, -1);
        t_light light = pointLight(point(0, 0, 10), color(1, 1, 1));

        Color   result = lighting(m, light, position, eyev, normalv, false);

        CHECK(result == color(0.1, 0.1, 0.1));
    }

    TEST(lighting_with_surface_in_shadow) {
        t_material  m = t_material();
        Point   position = point(0, 0, 0);
        Vec eyev = vec(0, 0, -1);
        Vec normalv = vec(0, 0, -1);
        t_light light = pointLight(point(0, 0, -10), color(1, 1, 1));
        bool    inShadow = true;

        Color   result = lighting(m, light, position, eyev, normalv, inShadow);

        CHECK(result == color (0.1, 0.1, 0.1));
    }

    TEST(there_is_no_shadow_when_nothing_is_collinear_with_point_and_light) {
        World   w = defaultWorld();
        Point   p = point(0, 10, 0);

        CHECK(w.isShadowed(p) == false);
    }

    TEST(shadow_when_an_object_is_between_point_and_light) {
        World   w = defaultWorld();
        Point   p = point(10, -10, 10);

        CHECK(w.isShadowed(p) == true);
    }

    TEST(there_is_no_shadow_when_an_object_is_behind_the_light) {
        World   w = defaultWorld();
        Point   p = point(-20, 20, -20);

        CHECK(w.isShadowed(p) == false);
    }

    TEST(there_is_no_shadow_when_an_object_is_behind_the_point) {
        World   w = defaultWorld();
        Point   p = point(-2, 2, -2);

        CHECK(w.isShadowed(p) == false);
    }
}
