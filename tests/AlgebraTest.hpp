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

	TEST(Matrix_tuple_multiplication) {
		Matrix	a((t_setMatrix) {
			1 ,2 ,3, 4,
			2, 4, 4, 2,
			8, 6, 4, 1,
			0, 0, 0, 1
		});

		Tuple	b(1, 2, 3, 1);
		Tuple	result = a * b;

		CheckTuple(Tuple(18, 24, 33, 1), result);
	}

	TEST(Identity_matrix_test) {
		Matrix a;
		Matrix	b((t_setMatrix) {
			1 ,2 ,3, 4,
			2, 4, 4, 2,
			8, 6, 4, 1,
			0, 0, 0, 1
		});
		Matrix	expected((t_setMatrix) {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		});

		a.setIdentity();
		b.setIdentity();
		CHECK(a == expected);
		CHECK(b == expected);
	}

	TEST(transposing_matrix_test) {
		Matrix a ((t_setMatrix){
			0, 9, 3, 0,
			9, 8, 0, 8,
			1, 8, 5, 3,
			0, 0, 5, 8
		});
		Matrix b = a.transpose();

		Matrix expected((t_setMatrix) {
			0, 9, 1, 0,
			9, 8, 8, 0,
			3, 0, 5, 5,
			0, 8, 3, 8
		});

		CHECK(b == expected);
	}

	TEST(inverting_matrix_test) {
		Matrix a((t_setMatrix){
			1, 5, 0, 0,
			-3, 2, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
		}, 2);

		double determinant = a.determinant();

		CHECK(determinant == 17);
	}

	TEST(submatrix_3by3) {
		Matrix a ((t_setMatrix) {
			1, 5, 0, 0,
			-3, 2, 7, 0,
			0, 6, -3, 0,
			0, 0, 0, 0
		});

		Matrix submatrix = a.submatrix(0, 2);

		Matrix expected((t_setMatrix){
			-3, 2, 0, 0,
			0, 6, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
		});

		Matrix b((t_setMatrix) {
			-6, 1, 1, 6,
			-8, 5, 8, 6,
			-1, 0, 8, 2,
			-7, 1, -1, 1
		});

		Matrix submatrix2 = b.submatrix(2, 1);

		Matrix expected2((t_setMatrix){
			-6, 1, 6, 0,
			-8, 8, 6, 0,
			-7, -1, 1, 0,
			0, 0, 0, 0
		}, 3);
		
		CHECK(submatrix == expected);
		CHECK(submatrix2 == expected2);
	}

	TEST(calculating_3x3_minor) {
		Matrix a((t_setMatrix) {
			3, 5, 0, 0,
			2, -1, -7, 0,
			6, -1, 5, 0,
			0, 0, 0, 0
		}, 3);

		Matrix submatrix = a.submatrix(1, 0);
		double determinant = submatrix.determinant();
		double minor = a.minor(1, 0);

		CHECK(minor == 25);
		CHECK(determinant == 25);
	}

	TEST(calculating_3x3_cofactor) {
		Matrix a((t_setMatrix) {
			3, 5, 0, 0,
			2, -1, -7, 0,
			6, -1, 5, 0,
			0, 0, 0, 0
		}, 3);

		double minor = a.minor(0, 0);
		double cofactor = a.cofactor(0, 0);
		double minor2 = a.minor(1, 0);
		double cofactor2 = a.cofactor(1, 0);

		CHECK(minor == -12);
		CHECK(cofactor == -12);
		CHECK(minor2 == 25);
		CHECK(cofactor2 == -25);
	}

	TEST(calculating_3x3_determinant) {
		Matrix a((t_setMatrix) {
			1, 2, 6, 0,
			-5, 8, -4, 0,
			2, 6, 4, 0,
			0, 0, 0, 0
		}, 3);

		CHECK(a.cofactor(0, 0) == 56);
		CHECK(a.cofactor(0, 1) == 12);
		CHECK(a.cofactor(0, 2) == -46);
		CHECK(a.determinant() == -196);
	}

	TEST(calculating_4x4_determinant) {
		Matrix a((t_setMatrix) {
			-2, -8, 3, 5,
			-3, 1, 7, 3,
			1, 2, -9, 6,
			-6, 7, 7, -9
		});

		CHECK(a.cofactor(0, 0) == 690);
		CHECK(a.cofactor(0, 1) == 447);
		CHECK(a.cofactor(0, 2) == 210);
		CHECK(a.cofactor(0, 3) == 51);
		CHECK(a.determinant() == -4071);
	}

	TEST(calculating_inverse_matrix) {
		Matrix a((t_setMatrix) {
			-5, 2, 6, -8,
			1, -5, 1, 8,
			7, 7, -6, -7,
			1, -3, 7, 4
		});

		Matrix expected((t_setMatrix) {
			0.21805, 0.45113, 0.24060, -0.04511,
			-0.80827, -1.45677, -0.44361, 0.52068,
			-0.07895, -0.22368, -0.05263, 0.19737,
			-0.52256, -0.81391, -0.30075, 0.30639
		});

		Matrix b = a.inverse();

		CHECK(areEqual(a.determinant(), 532.0));
		CHECK(areEqual(a.cofactor(2, 3), -160.0));
		CHECK(areEqual(b[3][2], -160.0/532.0));
		CHECK(areEqual(a.cofactor(3, 2), 105.0));
		CHECK(areEqual((b[2][3]), 105.0/532.0));
		CHECK(b == expected);

		Matrix c((t_setMatrix){
			8, -5, 9, 2,
			7, 5, 6, 1,
			-6, 0, 9, 6,
			-3, 0, -9, -4
		});

		Matrix cExpected((t_setMatrix){
			-0.15385, -0.15385, -0.28205, -0.53846,
			-0.07692, 0.12308, 0.02564, 0.03077,
			0.35897, 0.35897, 0.43590, 0.92308,
			-0.69231, -0.69231, -0.76923, -1.92308
		});

		CHECK(c.inverse() == cExpected);

		Matrix	d((t_setMatrix){
			9, 3, 0, 9,
			-5, -2, -6, -3,
			-4, 9, 6, 4,
			-7, 6, 6, 2
		});

		Matrix	dExpected((t_setMatrix) {
			-0.04074, -0.07778, 0.14444, -0.22222,
			-0.07778, 0.03333, 0.36667, -0.33333,
			-0.02901, -0.14630, -0.10926, 0.12963,
			0.17778, 0.06667, -0.26667, 0.33333
		});

		CHECK(dExpected == d.inverse());
	}

	TEST(multiplying_product_by_its_inverse) {
		Matrix	a((t_setMatrix) {
			3, -9, 7, 3,
			3, -8, 2, -9,
			-4, 4, 4, 1,
			-6, 5, -1, 1
		});

		Matrix	b((t_setMatrix) {
			8, 2, 2, 2,
			3, -1, 7, 0,
			7, 0, 5, 4,
			6, -2, 0, 5
		});

		Matrix c = a * b;
		CHECK((c * b.inverse()) == a);
	}

	TEST(mulplying_point_by_translation_matrix) {
		Matrix transform = translation(5, -3, 2);
		Point	p = point(-3, 4, 5);

		Point expected = point(2, 1, 7);

		CHECK((transform * p) == expected);
	}

	TEST(multiplying_by_inverse_translation_matrix) {
		Matrix transform = translation(5, -3, 2);
		Point	p = point(-3, 4, 5);
		Matrix	inverseTransform = transform.inverse();
		Point expected = point(-8, 7, 3);

		CHECK((inverseTransform * p) == expected);
	}

	TEST(translation_does_not_affect_vectors) {
		Matrix &&transform = translation(5, -3, 2);
		Vec		v = vector(-3, 4, 5);

		CHECK((transform * v) == v);
	}

	TEST(multiplying_point_by_scaling_matrix) {
		Matrix transform = scaling(2, 3, 4);
		Point	p = point(-4, 6, 8);

		CHECK((transform * p) == point(-8, 18, 32));
	}

	TEST(multiplying_vec_by_scaling_matrix) {
		Matrix transform = scaling(2, 3, 4);

		Vec	v = vector(-4, 6, 8);

		CHECK((transform * v) == vector(-8, 18, 32));
	}

	TEST(multiply_by_invese_of_scaling_matrix) {
		Matrix transform = scaling(2, 3, 4);

		Matrix inverse = transform.inverse();
		Vec	v = vector(-4, 6, 8);

		CHECK((inverse * v) == vector(-2, 2, 2));
	}

	TEST(scaling_by_negative) {
		Matrix transform = scaling(-1, 1, 1);

		Matrix inverse = transform.inverse();
		Point	p = point(2, 3 , 4);

		CHECK((inverse * p) == point(-2, 3, 4));
	}

	TEST(rotating_point_around_x_axis) {
		Point	p = point(0, 1, 0);

		Matrix	half_quarter = rotationX(M_PI / 4.0);
		Matrix	full_quarter = rotationX(M_PI / 2.0);
		Point	result = half_quarter * p;
		CHECK(result == point(0, sqrt(2.0) / 2.0, sqrt(2.0) / 2.0));
		CHECK((full_quarter * p) == point(0, 0, 1));
	}
	
	TEST(inverse_of_x_rotation) {
		Point p = point(0, 1, 0);
		
		Matrix half_quarter = rotationX(M_PI / 4);
		Matrix	inverse = half_quarter.inverse();
		
		CHECK((inverse * p) == point(0, sqrt(2) / 2, -sqrt(2) / 2));
	}

	TEST(rotating_point_around_y_axis) {
		Point	p = point(0, 0, 1);
	
		Matrix	half_quarter = rotationY(M_PI / 4.0);
		Matrix	full_quarter = rotationY(M_PI / 2.0);

		CHECK((half_quarter * p) == point(sqrt(2.0) / 2.0, 0, sqrt(2.0) / 2.0));
		CHECK((full_quarter * p) == point(1, 0, 0));
	}

	TEST(rotating_point_around_z_axis) {
		Point	p = point(0, 1, 0);
	
		Matrix	half_quarter = rotationZ(M_PI / 4.0);
		Matrix	full_quarter = rotationZ(M_PI / 2.0);

		CHECK((half_quarter * p) == point(-sqrt(2.0) / 2.0, sqrt(2.0) / 2.0, 0));
		CHECK((full_quarter * p) == point(-1, 0, 0));
	}

	TEST(shearing_transformation_moves_x_proportion_to_y) {
		Matrix	transform = shearing(1, 0, 0, 0, 0, 0);

		Point	p = point(2, 3, 4);

		CHECK((transform * p) == point(5, 3, 4));
	}

	TEST(shearing_transformation_moves_x_proportion_to_z) {
		Matrix	transform = shearing(0, 1, 0, 0, 0, 0);

		Point	p = point(2, 3, 4);

		CHECK((transform * p) == point(6, 3, 4));
	}

	TEST(shearing_transformation_moves_y_proportion_to_x) {
		Matrix	transform = shearing(0, 0, 1, 0, 0, 0);

		Point	p = point(2, 3, 4);

		CHECK((transform * p) == point(2, 5, 4));
	}

	TEST(shearing_transformation_moves_y_proportion_to_z) {
		Matrix	transform = shearing(0, 0, 0, 1, 0, 0);

		Point	p = point(2, 3, 4);

		CHECK((transform * p) == point(2, 7, 4));
	}

	TEST(shearing_transformation_moves_z_proportion_to_x) {
		Matrix	transform = shearing(0, 0, 0, 0, 1, 0);

		Point	p = point(2, 3, 4);

		CHECK((transform * p) == point(2, 3, 6));
	}

	TEST(shearing_transformation_moves_z_proportion_to_y) {
		Matrix	transform = shearing(0, 0, 0, 0, 0, 1);

		Point	p = point(2, 3, 4);

		CHECK((transform * p) == point(2, 3, 7));
	}

	TEST(individual_transformations_in_sequence) {
		Point	p = point(1, 0, 1);

		Matrix	a = rotationX(M_PI / 2);
		Matrix	b = scaling(5, 5, 5);
		Matrix	c = translation(10, 5, 7);

		Point	p2 = a * p;
		CHECK(p2 == point(1, -1, 0));

		Point	p3 = b * p2;
		CHECK(p3 == point(5, -5, 0));

		Point	p4 = c * p3;
		CHECK(p4 == point(15, 0 ,7));
	}

	TEST(chained_transformation_in_reverse) {
		Point	p = point(1, 0, 1);

		Matrix	a = rotationX(M_PI / 2);
		Matrix	b = scaling(5, 5, 5);
		Matrix	c = translation(10, 5, 7);

		Matrix t = c * b * a;

		CHECK((t * p) == point(15, 0, 7));
	}

	TEST(chaining_fluent_API) {
		Point	p = point(1, 0, 1);

		Matrix transform;

		transform.setIdentity()
		.rotateX(M_PI / 2)
		.scale(5, 5, 5)
		.translate(10, 5, 7);

		CHECK((transform * p) == point(15, 0, 7));
	}	
	
}

#endif /* ALGEBRATEST_HPP */
