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

		Matrix(int size=4);
		Matrix(t_setMatrix elements, int size = 4);
		Matrix(Matrix const &rhs);
		~Matrix();

		Matrix	&operator=(Matrix const &rhs);
		double	*operator[](int i);
		const double	*operator[](int i) const;
		bool	operator==(Matrix const &rhs) const;
		Matrix	operator*(Matrix const &rhs) const;

		Matrix	transpose(void) const;
		Matrix	submatrix(int row, int column) const;
		double	determinant() const;
		double	minor(int row, int column) const;
		double	cofactor(int row, int column) const;
		Matrix	inverse(void) const;
		
		Matrix	&setIdentity(void);
		Matrix	&translate(double x, double y, double z);
		Matrix	&scale(double x, double y, double z);
		Matrix	&rotateX(double rad);
		Matrix	&rotateY(double rad);
		Matrix	&rotateZ(double rad);
		Matrix	&shear(double xy, double xx, double yx, double yz, double zx, double zy);

		int		getSize(void) const;
		
		friend	ostream	&operator<<(ostream &o, Matrix const &rhs);
		
		private:
		
		double	_matrix[4][4];
		int		_size;
		void	checkSize(int size);
		void	switchRows(int row1, int row2);
		void	switchColumns(int column1, int column2);
		void	switchRowtoEnd(int row);
		void	switchColumntoEnd(int column);
		void	deleteRow(int row);
		void	deleteColumn(int Column);
		double	determinantTwoByTwo(void) const;
};

Matrix	translation(double x, double y, double z);
Matrix	scaling(double x, double y, double z);
Matrix	rotationX(double rad);
Matrix	rotationY(double rad);
Matrix	rotationZ(double rad);
Matrix	shearing(double xy, double xz, double yx, double yz, double zx, double zy);

#endif /* MATRIX_HPP */
