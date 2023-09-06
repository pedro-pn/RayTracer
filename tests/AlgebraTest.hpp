#ifndef ALGEBRATEST_HPP
# define ALGEBRATEST_HPP

# include "../include/algebra.hpp"
# include <UnitTest++/UnitTest++.h>
# include "TestUtils.hpp"
#include <math.h>

SUITE(ALGEBRA_TEST) {
	TEST(POINT_TEST) {
		Point	p = point(4.3, -4.2, 3.1);

		TestTuple(p, 4.3, -4.2, 3.1, POINT);
	}

	TEST(VECTOR_TEST) {
		Vec v = vector(4.3, -4.2, 3.1);

		TestTuple(v, 4.3, -4.2, 3.1, VECTOR);
	}

	TEST(SUBTRACT_POINTS) {
		Point	p1 = point(3, 2, 1);
		Point	p2 = point(5, 6, 7);

		CheckTuple(vector(-2, -4, -6), p1 - p2);
	}

	TEST(SUBTRACT_VEC_FROM_POINT) {
		Point	p = point(3, 2, 1);
		Vec		v = vector(5, 6, 7);

		CheckTuple(point(-2, -4, -6), p - v);
	}

	TEST(SUBTRACT_TWO_VECTORS) {
		Vec	v1 = vector(3, 2, 1);
		Vec	v2 = vector(5, 6, 7);

		CheckTuple(vector(-2, -4, -6), v1 - v2);
	}

	TEST(NEGATING_TUPLE) {
		Vec	zero;
		Vec	v = vector(1, -2, 3);

		CheckTuple(vector(-1, 2, -3), zero - v);
		CheckTuple(vector(-1, 2, -3), -v);
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
		Vec expt = vector(1, 0, 0);
		CheckTuple(expt, v.normalize());

		v = vector(1, 2, 3);
		expt = vector(1 / sqrt(14), 2 / sqrt(14), 3 / sqrt(14));
		CheckTuple(expt, v.normalize());

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

		CheckTuple(vector(-1, 2, -1), cross(a, b));
		CheckTuple(vector(1, -2, 1), cross(b, a));
	}

	TEST(ADD_COLORS_TEST) {
		Color c1 = color(0.9, 0.6, 0.75);
		Color c2 = color(0.7, 0.1, 0.25);

		Color expt = color(1.6, 0.7, 1.0);
		CheckTuple(expt, c1 + c2);
	}

	TEST(SUBTRACTING_COLORS_TEST) {
		Color c1 = color(0.9, 0.6, 0.75);
		Color c2 = color(0.7, 0.1, 0.25);

		Color expt = color(0.2, 0.5, 0.5);
		CheckTuple(expt, c1 - c2);
	}

	TEST(MULTIPLYING_COLORS_BY_SCALAR_TEST) {
		Color c1 = color(0.2, 0.3, 0.4);

		CheckTuple(color(0.4, 0.6, 0.8), 2 * c1);
	}

	TEST(MULTIPLYING_COLORS_TEST) {
		Color c1 = color(1, 0.2, 0.4);
		Color c2 = color(0.9, 1, 0.1);

		Color expt = color(0.9, 0.2, 0.04);
		CheckTuple(expt, c1 * c2);
	}
}

SUITE(MATRIX_TEST) {
	TEST(twobytwoTEST) {
		Matrix	m;
		m[0][0] = -3;
		m[0][1] = 5;
		m[1][0] = 1;
		m[1][1] = -2;
		
		CHECK_CLOSE(-3, m[0][0], EPSILON);
		CHECK_CLOSE(5, m[0][1], EPSILON);
		CHECK_CLOSE(1, m[1][0], EPSILON);
		CHECK_CLOSE(-2, m[1][1], EPSILON);
		CHECK_CLOSE(0, m[1][2], EPSILON);
	}

	TEST(TEST_EQUAL_OPERATOR) {
		bool	isEqual;
		Matrix a((t_setMatrix){
			1, 2, 3, 4,
			5, 6, 7, 8,
			9, 8, 7, 6,
			5, 4, 3, 2
		});
		Matrix b((t_setMatrix){
			1, 2, 3, 4,
			5, 6, 7, 8,
			9, 8, 7, 6,
			5, 4, 3, 2
		});

		isEqual = a == b;

		CHECK(isEqual);
	}

	TEST(MATRIX_MULTIPLICATION) {
		Matrix a((t_setMatrix) {
			1, 2, 3, 4,
			5, 6, 7, 8,
			9, 8, 7, 6,
			5, 4, 3, 2
		});

		Matrix b((t_setMatrix) {
			-2, 1, 2, 3,
			3, 2, 1, -1,
			4, 3, 6, 5,
			1, 2, 7, 8
		});

		Matrix	expected((t_setMatrix) {
			20, 22, 50 ,48,
			44, 54, 114, 108,
			40, 58, 110, 102,
			16, 26, 46 ,42
		});

		Matrix result = a * b;

		bool	isEqual = result == expected;
		CHECK(isEqual);
	}
}

#endif /* ALGEBRATEST_HPP */
