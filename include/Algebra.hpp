#ifndef ALGEBRA_HPP
# define ALGEBRA_HPP

# include "Tuple.hpp"
# include "Matrix.hpp"
# include <cmath>

# define EPSILON 1E-4

class Matrix;
class Tuple;

// Matrix operators

Tuple	operator*(Matrix const &matrix, Tuple const &tuple);

bool	areEqual(double n1, double n2);

#endif /* ALGEBRA_HPP */
