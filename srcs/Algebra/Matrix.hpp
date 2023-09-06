#ifndef MATRIX_HPP
# define MATRIX_HPP

# include <iostream>
# include <cmath>
# include "algebra.hpp"

using namespace std;

typedef double	t_matrix[16];

typedef struct s_setMatrix {
	double		elements[16];
}			t_setMatrix;

class Matrix {

	public:

		Matrix();
		Matrix(t_setMatrix elements);
		Matrix(Matrix const &rhs);
		~Matrix();

		Matrix	&operator=(Matrix const &rhs);
		double	*operator[](int i);
		bool	operator==(Matrix const &rhs) const;
		Matrix	operator*(Matrix const &rhs) const;

		friend	ostream	&operator<<(ostream &o, Matrix const &rhs);

	private:

		double	matrix[4][4];
};

#endif /* MATRIX_HPP */
