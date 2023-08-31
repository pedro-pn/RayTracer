#ifndef TESTUTILS_HPP
# define TESTUTILS_HPP
# define EPSILON 1E-4

void	TestTuple(Tuple const &tuple, double x, double y, double z, double w) {
	CHECK_CLOSE(x, tuple.x, EPSILON);
	CHECK_CLOSE(y, tuple.y, EPSILON);
	CHECK_CLOSE(z, tuple.z, EPSILON);
	CHECK_CLOSE(w, tuple.w, EPSILON);
}

#endif /* TESTUTILS_HPP*/
