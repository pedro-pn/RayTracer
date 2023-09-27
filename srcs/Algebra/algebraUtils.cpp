#include "algebra.hpp"

bool	areEqual(double n1, double n2) {
	double	diff;

	diff = fabs(n1 - n2);
	if (diff > EPSILON)
		return (false);
	return (true);
}

Tuple	operator*(Matrix const &matrix, Tuple const &tuple) {
	Matrix	tupleMatrix;
	Matrix	result;

	tupleMatrix[0][0] = tuple.x;
	tupleMatrix[1][0] = tuple.y;
	tupleMatrix[2][0] = tuple.z;
	tupleMatrix[3][0] = tuple.w;
	
	result = matrix * tupleMatrix;
	return (Tuple(result[0][0], result[1][0], result[2][0], result[3][0]));
}
