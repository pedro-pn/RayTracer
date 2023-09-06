#include "algebra.hpp"

bool	areEqual(double n1, double n2) {
	double	diff;

	diff = fabs(n1 - n2);
	if (diff > EPSILON)
		return (false);
	return (true);
}
