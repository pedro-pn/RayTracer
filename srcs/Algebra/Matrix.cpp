#include "Matrix.hpp"
#include <exception>
#include <cstring>

Matrix::Matrix() : matrix{0} {
}

Matrix::Matrix(t_setMatrix elements) {
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++)
			matrix[i][j] = elements.elements[(i * 4)+ j];
	}
}

Matrix::~Matrix() {
}

Matrix::Matrix(Matrix const &rhs) : Matrix() {
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++)
			matrix[i][j] = rhs.matrix[i][j];
	}
}

Matrix	&Matrix::operator=(Matrix const &rhs) {
	if (this == &rhs)
		return (*this);
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++)
			matrix[i][j] = rhs.matrix[i][j];
	}
	return (*this);
}

double	*Matrix::operator[](int i) {
	return (this->matrix[i]);
}

bool	Matrix::operator==(Matrix const &rhs) const {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (areEqual(this->matrix[i][j], rhs.matrix[i][j]) == false)
				return (false);
		}
	}
	return (true);
}

Matrix	Matrix::operator*(Matrix const &rhs) const {
	Matrix	result;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result[i][j] = this->matrix[i][0] * rhs.matrix[0][j] +
						this->matrix[i][1] * rhs.matrix[1][j] +
						this->matrix[i][2] * rhs.matrix[2][j]+
						this->matrix[i][3] * rhs.matrix[3][j];
		}
	}
	return (result);
}

void	Matrix::setIdentity(void) {
	bzero(this->matrix, 16 * sizeof(double));
	this->matrix[0][0] = 1;
	this->matrix[1][1] = 1;
	this->matrix[2][2] = 1;
	this->matrix[3][3] = 1;
}

ostream	&operator<<(ostream &o, Matrix const &rhs) {
	for (int i = 0; i < 4; i++) {
		o << "(";
		for (int j = 0; j < 4; j++) {
			o << rhs.matrix[i][j];
			if (j < 3)
				o << ", ";
		}
		o << ")";
		if (i < 3)
			o << "\n";
	}
	return (o);
}
