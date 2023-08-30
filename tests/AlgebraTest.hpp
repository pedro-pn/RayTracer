#ifndef ALGEBRATEST_HPP
# define ALGEBRATEST_HPP

# include "../include/algebra.h"
# include <UnitTest++/UnitTest++.h>
# include "TestUtils.hpp"
#include <math.h>

SUITE(ALGEBRA_TEST) {
	TEST(POINT_TEST) {
		Point	point(4.3, -4.2, 3.1);

		TestTuple<Point>(point, 4.3, -4.2, 3.1, 1);
	}

	TEST(VECTOR_TEST) {
		Vec vector(4.3, -4.2, 3.1);

		TestTuple<Vec>(vector, 4.3, -4.2, 3.1, 0);
	}

	TEST(SUBTRACT_POINTS) {
		Point	p1(3, 2, 1);
		Point	p2(5, 6, 7);

		TestTuple<Vec>(p1 - p2, -2, -4, -6, 0);
	}

	TEST(SUBTRACT_VEC_FROM_POINT) {
		Point	p(3, 2, 1);
		Vec		v(5, 6, 7);

		TestTuple<Point>(p - v, -2, -4, -6, 1);
	}

	TEST(SUBTRACT_TWO_VECTORS) {
		Vec	v1(3, 2, 1);
		Vec	v2(5, 6, 7);

		TestTuple<Vec>(v1 - v2, -2, -4, -6, 0);
	}

	TEST(NEGATING_TUPLE) {
		Vec	zero;
		Vec	v(1, -2, 3);

		TestTuple<Vec>(zero - v, -1, 2, -3, 0);
		TestTuple<Vec>(-v, -1, 2, -3, 0);
	}

	TEST(SCALAR_MULTIPLICATION_DIVISION) {
		Point	p(1, -2, 3);
		Vec		v(1, -2, 3);

		TestTuple<Point>(p * 3.5, 3.5, -7, 10.5, 1);
		TestTuple<Vec>(v * 3.5, 3.5, -7, 10.5, 0);
		TestTuple<Point>(p / 2, 0.5, -1, 1.5, 1);
		TestTuple<Vec>(v / 2, 0.5, -1, 1.5, 0);
	}

	TEST(MAGNITUDE_TEST) {
		Vec	v(1, 0, 0);
		CHECK_CLOSE(1, v.magnitude(), EPSILON);

		v = Vec(0, 1, 0);
		CHECK_CLOSE(1, v.magnitude(), EPSILON);

		v = Vec(0, 0, 1);
		CHECK_CLOSE(1, v.magnitude(), EPSILON);

		v = Vec(1, 2, 3);
		CHECK_CLOSE(sqrt(14), v.magnitude(), EPSILON);

		v = Vec(-1, -2, -3);
		CHECK_CLOSE(sqrt(14), v.magnitude(), EPSILON);
	}

	TEST(NORMALIZE_TEST) {
		Vec v(4, 0, 0);
		TestTuple<Vec>(v.normalize(), 1, 0, 0, 0);

		v = Vec(1, 2, 3);
		TestTuple<Vec>(v.normalize(), 1 / sqrt(14), 2 / sqrt(14), 3 / sqrt(14), 0);

		CHECK_CLOSE((v.normalize()).magnitude(), 1, EPSILON);
	}

	TEST(DOT_PRODUCT_TEST) {
		Vec a(1, 2, 3);
		Vec b(2, 3, 4);

		CHECK_CLOSE(20, dot(a, b), EPSILON);
	}

	TEST(CROSS_PRODUCT_TEST) {
		Vec a(1, 2, 3);
		Vec b(2, 3, 4);

		TestTuple(cross(a, b), -1, 2, -1, 0);
		TestTuple(cross(b, a), 1, -2, 1, 0);
	}
}


#endif /* ALGEBRATEST_HPP */
