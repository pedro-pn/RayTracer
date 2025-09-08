#pragma once

#include <UnitTest++/UnitTest++.h>
#include "TestUtils.hpp"
#include "RayTracer.hpp"

SUITE(WORLD_TESTS) {

	TEST(default_world) {
		t_light light = pointLight(point(-10, 10, -10), color(1, 1, 1));
		Sphere  s1 = Sphere();
		t_material  m = t_material();
		m.colour = color(0.8, 1.0, 0.6);
		m.diffuse = 0.7,
		m.specular = 0.2;
		s1.setMaterial(m);
		Sphere s2 = Sphere();
		s2.setTransform(Matrix().setIdentity().scale(0.5, 0.5, 0.5));

		World   w = defaultWorld();

		CHECK(w.getLight() == light);
		CHECK(w.getObjects()[0] == s1);
		CHECK(w.getObjects()[1] == s2);

	}

	TEST(intersect_world_with_a_ray) {
		World   w = defaultWorld();
		t_ray   r = ray(point(0, 0, -5), vec(0, 0, 1));
		t_intersect xs = w.intersectWorld(r);

		CHECK(xs.count == 4);
		CHECK(xs.intersections[0].t == 4);
		CHECK(xs.intersections[1].t == 4.5);
		CHECK(xs.intersections[2].t == 5.5);
		CHECK(xs.intersections[3].t == 6);
	}

	TEST(precomputing_state_of_intersection) {
		t_ray   r = ray(point(0, 0, -5), vec(0, 0, 1));
		Sphere  s;
		t_intersection  inter = intersection(4, s);

		t_computations   comps = prepareComputations(inter, r);

		CHECK(comps.t == inter.t);
		CHECK(comps.object == inter.object);
		CHECK(comps.point == point(0, 0, -1));
		CHECK(comps.eyev == vec(0, 0, -1));
		CHECK(comps.normalv == vec(0, 0, -1));
	}

	TEST(hit_when_an_intersection_occurs_on_the_outside) {
		t_ray   r = ray(point(0, 0, -5), vec(0, 0, 1));
		Sphere  s;
		t_intersection  inter = intersection(4, s);

		t_computations   comps = prepareComputations(inter, r);

		CHECK(comps.inside == false);
	}

	TEST(hit_when_an_intersection_occurs_on_the_inside) {
		t_ray   r = ray(point(0, 0, 0), vec(0, 0, 1));
		Sphere  s;
		t_intersection  inter = intersection(1, s);

		t_computations   comps = prepareComputations(inter, r);

		CHECK(comps.point == point(0, 0, 1));
		CHECK(comps.eyev == vec(0, 0, -1));
		CHECK(comps.inside == true);
		CHECK(comps.normalv == vec(0, 0, -1));
	}

	TEST(shading_an_intersection) {
		t_ray   r = ray(point(0, 0, -5), vec(0, 0, 1));
		World   w = defaultWorld();
		t_intersection  inter = intersection(4, w.getObjects()[0]);

		
		t_computations   comps = prepareComputations(inter, r);
		Color   c = shadeHit(w, comps);

		CHECK(c == color(0.38066, 0.47583, 0.2855));
	}
	
	TEST(shading_an_intersection_from_the_inside) {
		t_ray   r = ray(point(0, 0, 0), vec(0, 0, 1));
		World   w = defaultWorld();
		w.setLight(pointLight(point(0, 0.25, 0), color(1, 1, 1)));
		
		
		
		t_intersection  inter = intersection(0.5, w.getObjects()[1]);
		t_computations   comps = prepareComputations(inter, r);
		Color   c = shadeHit(w, comps);

		CHECK(c == color(0.90498, 0.90498, 0.90498));
	}

	TEST(shade_is_given_an_intersection_in_shadow) {
		World	w;
		w.setLight(pointLight(point(0, 0, -10), color(1, 1, 1)));
		Sphere	s1;
		Sphere	s2;

		w.addObject(s1);
		s2.getTransform().translate(0, 0, 10);
		w.addObject(s2);
		t_ray	r = ray(point(0, 0, 5), vec(0, 0, 1));
		t_intersection inter = intersection(4, s2);
		t_computations comps = prepareComputations(inter, r);
		Color c = shadeHit(w, comps);

		CHECK(c == color(0.1, 0.1, 0.1));
	}

	TEST(hit_should_offset_the_point) {
		t_ray	r = ray(point(0, 0, -5), vec(0, 0, 1));
		Sphere	s;

		s.getTransform().translate(0, 0, 1);
		t_intersection	inter = intersection(5, s);
		t_computations	comps = prepareComputations(inter, r);

		CHECK(comps.overPoint.z < -EPSILON / 2);
		CHECK(comps.point.z > comps.overPoint.z);
	}

	TEST(color_when_ray_misses) {
		World   w = defaultWorld();
		t_ray   r = ray(point(0, 0, -5), vec(0, 1, 0));

		Color   c = colorAt(w, r);

		CHECK(c == color(0, 0, 0));
	}

	TEST(color_when_ray_hits) {
		World   w = defaultWorld();
		t_ray   r = ray(point(0, 0, -5), vec(0, 0, 1));

		Color   c = colorAt(w, r);

		CHECK(c == color(0.38066, 0.47583, 0.2855));
	}

	TEST(color_with_intersection_behind_the_ray) {
		World   w = defaultWorld();

		w.getObjects()[0].getMaterial().ambient = 1;
		w.getObjects()[1].getMaterial().ambient = 1;

		t_ray   r = ray(point(0, 0, 0.75), vec(0, 0, -1));

		Color   c = colorAt(w, r);

		CHECK(c ==  w.getObjects()[1].getMaterial().colour);
	}

	TEST(transformation_matrix_for_the_default_orientation) {
		Point	from = point(0, 0, 0);
		Point	to = point(0, 0, -1);
		Vec		up = vec(0, 1, 0);

		Matrix	t = viewTransformation(from, to, up);

		CHECK(t == Matrix().setIdentity());
	}

	TEST(view_transformnation_matrix_looking_in_positive_z_direction) {
		Point	from = point(0, 0, 0);
		Point	to = point(0, 0, 1);
		Vec		up = vec(0, 1, 0);

		Matrix	t = viewTransformation(from, to, up);

		CHECK(t == scaling(-1, 1, -1));
	}

	TEST(view_transformation_moves_the_world) {
		Point	from = point(0, 0, 8);
		Point	to = point(0, 0, 0);
		Vec		up = vec(0, 1, 0);

		Matrix	t = viewTransformation(from, to, up);

		CHECK(t == translation(0, 0, -8));
	}

	TEST(an_arbitrary_view_transformation) {
		Point	from = point(1, 3, 2);
		Point	to = point(4, -2, 8);
		Vec		up = vec(1, 1, 0);

		Matrix	t = viewTransformation(from, to, up);

		Matrix	result = Matrix((t_setMatrix){
			-0.50709, 0.50709, 0.67612, -2.36643,
			0.76772, 0.60609, 0.12122, -2.82843,
			-0.35857, 0.59761, -0.71714, 0.00000,
			0.00000, 0.00000, 0.00000, 1.00000
		});

		CHECK(t == result);
	}

	TEST(constructing_a_camera) {
		Camera	cam = Camera(160, 120, M_PI / 2);

		CHECK(cam.hsize == 160);
		CHECK(cam.vsize == 120);
		CHECK(cam.fieldOfView == M_PI / 2);
		CHECK(cam.getTransform() == Matrix().setIdentity());
	}

	TEST(pixel_size_for_horizontal_canvas) {
		Camera	cam = Camera(200, 125, M_PI / 2);

		CHECK(areEqual(cam.pixelSize, 0.01));
	}

	TEST(pixel_size_for_vertical_canvas) {
		Camera	cam = Camera(125, 200, M_PI / 2);
		
		CHECK(areEqual(cam.pixelSize, 0.01));
	}

	TEST(constructing_ray_through_center_of_canvas) {
		Camera	c = Camera(201, 101, M_PI / 2);
		t_ray	r = c.rayForPixel(100, 50);

		CHECK(r.origin == point(0, 0, 0));
		CHECK(r.direction == vec(0, 0, -1));
	}

	TEST(constructing_ray_through_a_corner_of_canvas) {
		Camera	c = Camera(201, 101, M_PI / 2);
		t_ray	r = c.rayForPixel(0, 0);

		CHECK(r.origin == point(0, 0, 0));
		CHECK(r.direction == vec(0.66519, 0.33259, -0.66851));
	}

	TEST(constructing_ray_when_camera_is_transformed) {
		Camera	c = Camera(201, 101, M_PI / 2);
		c.setTransform(rotationY(M_PI / 4) * translation(0, -2, 5));
		t_ray	r = c.rayForPixel(100, 50);

		CHECK(r.origin == point(0, 2, -5));
		CHECK(r.direction == vec(sqrt(2) / 2, 0, -sqrt(2) / 2));
	}

	TEST(rendering_world_with_camera) {
		World	w = defaultWorld();
		Camera	c = Camera(11, 11, M_PI / 2);
		Point		from = point(0, 0, -5);
		Point		to = point(0, 0, 0);
		Vec			up = vec(0, 1, 0);

		c.setTransform(viewTransformation(from, to ,up));

		Canvas	image = c.render(w);
		int	colorPixel = image.getPixel(5, 5);
		CHECK(ColorUtils::pixelColorToColor(colorPixel) == color(0.384314, 0.478431, 0.286275));
	}
}
