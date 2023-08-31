#ifndef ALGEBRATEST_HPP
# define ALGEBRATEST_HPP

# include "../include/algebra.h"
# include <UnitTest++/UnitTest++.h>
# include "TestUtils.hpp"
#include <math.h>

SUITE(ALGEBRA_TEST) {
	TEST(POINT_TEST) {
		Point	p = point(4.3, -4.2, 3.1);

		TestTuple(p, 4.3, -4.2, 3.1, 1);
	}

	TEST(VECTOR_TEST) {
		Vec v = vector(4.3, -4.2, 3.1);

		TestTuple(v, 4.3, -4.2, 3.1, 0);
	}

	TEST(SUBTRACT_POINTS) {
		Point	p1 = point(3, 2, 1);
		Point	p2 = point(5, 6, 7);

		TestTuple(p1 - p2, -2, -4, -6, 0);
	}

	TEST(SUBTRACT_VEC_FROM_POINT) {
		Point	p = point(3, 2, 1);
		Vec		v = vector(5, 6, 7);

		TestTuple(p - v, -2, -4, -6, 1);
	}

	TEST(SUBTRACT_TWO_VECTORS) {
		Vec	v1 = vector(3, 2, 1);
		Vec	v2 = vector(5, 6, 7);

		TestTuple(v1 - v2, -2, -4, -6, 0);
	}

	TEST(NEGATING_TUPLE) {
		Vec	zero;
		Vec	v = vector(1, -2, 3);

		TestTuple(zero - v, -1, 2, -3, 0);
		TestTuple(-v, -1, 2, -3, 0);
	}

	TEST(SCALAR_MULTIPLICATION_DIVISION) {
		Point	p = point(1, -2, 3);
		Vec		v = vector(1, -2, 3);

		TestTuple(p * 3.5, 3.5, -7, 10.5, 3.5);
		TestTuple(v * 3.5, 3.5, -7, 10.5, 0);
		TestTuple(p / 2, 0.5, -1, 1.5, 0.5);
		TestTuple(v / 2, 0.5, -1, 1.5, 0);
	}

	TEST(MAGNITUDE_TEST) {
		Vec	v = vector(1, 0, 0);
		CHECK_CLOSE(1, v.magnitude(), EPSILON);

		v = vector(0, 1, 0);
		CHECK_CLOSE(1, v.magnitude(), EPSILON);

		v = vector(0, 0, 1);
		CHECK_CLOSE(1, v.magnitude(), EPSILON);

		v = vector(1, 2, 3);
		CHECK_CLOSE(sqrt(14), v.magnitude(), EPSILON);

		v = vector(-1, -2, -3);
		CHECK_CLOSE(sqrt(14), v.magnitude(), EPSILON);
	}

	TEST(NORMALIZE_TEST) {
		Vec v = vector(4, 0, 0);
		TestTuple(v.normalize(), 1, 0, 0, 0);

		v = vector(1, 2, 3);
		TestTuple(v.normalize(), 1 / sqrt(14), 2 / sqrt(14), 3 / sqrt(14), 0);

		CHECK_CLOSE((v.normalize()).magnitude(), 1, EPSILON);
	}

	TEST(DOT_PRODUCT_TEST) {
		Vec a = vector(1, 2, 3);
		Vec b = vector(2, 3, 4);

		CHECK_CLOSE(20, dot(a, b), EPSILON);
	}

	TEST(CROSS_PRODUCT_TEST) {
		Vec a = vector(1, 2, 3);
		Vec b = vector(2, 3, 4);

		TestTuple(cross(a, b), -1, 2, -1, 0);
		TestTuple(cross(b, a), 1, -2, 1, 0);
	}
}


#endif /* ALGEBRATEST_HPP */
