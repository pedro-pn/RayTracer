#pragma once

void	TestTuple(Tuple const &tuple, double x, double y, double z, double w) {
	CHECK_CLOSE(x, tuple.x, EPSILON);
	CHECK_CLOSE(y, tuple.y, EPSILON);
	CHECK_CLOSE(z, tuple.z, EPSILON);
	CHECK_CLOSE(w, tuple.w, EPSILON);
}

void	CheckTuple(Tuple const &expected, Tuple const &result) {
	CHECK_CLOSE(expected.x, result.x, EPSILON);
	CHECK_CLOSE(expected.y, result.y, EPSILON);
	CHECK_CLOSE(expected.z, result.z, EPSILON);
	CHECK_CLOSE(expected.w, result.w, EPSILON);
}
