#include "Matrix.hpp"
#include <exception>
#include <cstring>


void	Matrix::checkSize(int size) {
	if (size < 2 || size > 4)
		throw std::out_of_range("Matrix size must be 2, 3 or 4.");
}

Matrix::Matrix(int size) : _matrix{0}, _size(size) {
	this->checkSize(size);
}

Matrix::Matrix(t_setMatrix elements, int size) : _size(size) {
	this->checkSize(size);
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++)
			_matrix[i][j] = elements.elements[(i * 4)+ j];
	}
}

Matrix::~Matrix() {
}

Matrix::Matrix(Matrix const &rhs) : Matrix(rhs._size) {
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++)
			_matrix[i][j] = rhs._matrix[i][j];
	}
}

Matrix	&Matrix::operator=(Matrix const &rhs) {
	if (this == &rhs)
		return (*this);
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++)
			_matrix[i][j] = rhs._matrix[i][j];
	}
	return (*this);
}

double	*Matrix::operator[](int i) {
	return (this->_matrix[i]);
}

const double	*Matrix::operator[](int i) const {
	return (this->_matrix[i]);
}

bool	Matrix::operator==(Matrix const &rhs) const {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (areEqual(this->_matrix[i][j], rhs._matrix[i][j]) == false)
				return (false);
		}
	}
	return (true);
}

int	Matrix::getSize(void) const {
	return (this->_size);
}

Matrix	Matrix::operator*(Matrix const &rhs) const {
	Matrix	result;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result[i][j] = this->_matrix[i][0] * rhs._matrix[0][j] +
						this->_matrix[i][1] * rhs._matrix[1][j] +
						this->_matrix[i][2] * rhs._matrix[2][j]+
						this->_matrix[i][3] * rhs._matrix[3][j];
		}
	}
	return (result);
}

void	Matrix::setIdentity(void) {
	bzero(this->_matrix, 16 * sizeof(double));
	this->_matrix[0][0] = 1;
	this->_matrix[1][1] = 1;
	this->_matrix[2][2] = 1;
	this->_matrix[3][3] = 1;
}

Matrix	Matrix::transpose(void) const {
	Matrix transposed;

	for (int i  = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			transposed[j][i] = _matrix[i][j];
		}
	}
	return (transposed);
}

/// @brief This determinant treats the matrix as a 2x2 matrix.
/// @param  
/// @return The determinant
double	Matrix::determinantTwoByTwo(void) const {
	return ((_matrix[0][0] * _matrix[1][1]) - (_matrix[0][1] * _matrix[1][0]));
}

void	Matrix::switchRows(int row1, int row2) {
	Tuple	tempRow(_matrix[row1][0], _matrix[row1][1], _matrix[row1][2], _matrix[row1][3]);

	_matrix[row1][0] = _matrix[row2][0];
	_matrix[row1][1] = _matrix[row2][1];
	_matrix[row1][2] = _matrix[row2][2];
	_matrix[row1][3] = _matrix[row2][3];
	_matrix[row2][0] = tempRow.x;
	_matrix[row2][1] = tempRow.y;
	_matrix[row2][2] = tempRow.z;
	_matrix[row2][3] = tempRow.w;
}

void	Matrix::switchColumns(int column1, int column2) {
	Tuple	tempColumn(_matrix[0][column1], _matrix[1][column1], _matrix[2][column1], _matrix[3][column1]);

	_matrix[0][column1] = _matrix[0][column2];
	_matrix[1][column1] = _matrix[1][column2];
	_matrix[2][column1] = _matrix[2][column2];
	_matrix[3][column1] = _matrix[3][column2];
	_matrix[0][column2] = tempColumn.x;
	_matrix[1][column2] = tempColumn.y;
	_matrix[2][column2] = tempColumn.z;
	_matrix[3][column2] = tempColumn.w;
}

void	Matrix::switchRowtoEnd(int row) {
	while (row < 3) {
		this->switchRows(row, row + 1);
		row++;
	}
}

void	Matrix::switchColumntoEnd(int column) {
	while (column < 3) {
		this->switchColumns(column, column + 1);
		column++;
	}
}

void	Matrix::deleteRow(int row) {
	_matrix[row][0] = 0;
	_matrix[row][1] = 0;
	_matrix[row][2] = 0;
	_matrix[row][3] = 0;
}

void	Matrix::deleteColumn(int column) {
	_matrix[0][column] = 0;
	_matrix[1][column] = 0;
	_matrix[2][column] = 0;
	_matrix[3][column] = 0;
}

Matrix	Matrix::submatrix(int row, int column) const {
	Matrix submatrix(*this);

	submatrix.switchColumntoEnd(column);
	submatrix.switchRowtoEnd(row);
	submatrix.deleteColumn(3);
	submatrix.deleteRow(3);
	submatrix._size--;
	return (submatrix);
}

double	Matrix::minor(int row, int column) const {
	return (this->submatrix(row, column).determinant());
}

double Matrix::cofactor(int row, int column) const {
	return ((row + column) % 2 ? -this->minor(row, column): this->minor(row, column));
}

double	Matrix::determinant(void) const {
	double determinant = 0;

	if (this->_size == 2)
		determinant = this->determinantTwoByTwo();
	else {
		for (int column = 0; column < this->_size; column++) {
			determinant += _matrix[0][column] * this->cofactor(0, column);
		}
	}

	return (determinant);
}

Matrix	Matrix::inverse(void) const {
	if (this->determinant() == 0)
		return (*this);
	
	Matrix	inverse(this->_size);
	for (int row = 0; row < this->_size; row++) {
		for (int column = 0; column < this->_size; column++) {
			double cofactor = this->cofactor(row, column);
			inverse[column][row] = cofactor / this->determinant();
		}
	}

	return (inverse);
}

ostream	&operator<<(ostream &o, Matrix const &rhs) {
	for (int i = 0; i < 4; i++) {
		o << "(";
		for (int j = 0; j < 4; j++) {
			o << rhs._matrix[i][j];
			if (j < 3)
				o << ", ";
		}
		o << ")";
		if (i < 3)
			o << "\n";
	}
	return (o);
}
