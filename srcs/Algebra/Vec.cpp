#include "Vec.hpp"
#include <cmath>

Vec::Vec() : x(0), y(0), z(0), w(0) {
}

Vec::Vec(double x, double y, double z) : x(x), y(y), z(z), w(0) {
}

Vec::~Vec() {
}

Vec::Vec(Vec const &rhs) {
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
	this->w = rhs.w;
}

Vec	&Vec::operator=(Vec const &rhs) {
	if (this == &rhs)
		return (*this);
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
	this->w = rhs.w;
	return (*this);
}

Vec	Vec::operator+(Vec const &rhs) {
	double x, y, z;

	x = this->x + rhs.x;
	y = this->y + rhs.y;
	z = this->z + rhs.z;
	return (Vec(x, y, z));
}

Vec	Vec::operator-(Vec const &rhs) {
	double x, y, z;

	x = this->x - rhs.x;
	y = this->y - rhs.y;
	z = this->z - rhs.z;
	return (Vec(x, y, z));
}

Vec	Vec::operator-() {
	return (Vec(0, 0, 0) - *this);
}

Vec	Vec::operator*(double n) {
	return (Vec(this->x * n, this->y * n, this->z * n));
}

Vec	Vec::operator/(double n) {
	return (Vec(this->x / n, this->y / n, this->z / n));
}

double	Vec::magnitude(void) const {
	return (sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2)));
}

Vec	Vec::normalize(void) const {
	double	mag;

	mag = this->magnitude();
	return (Vec(x / mag, y / mag, z / mag));
}


// related

ostream&	operator<<(ostream &o, Vec const &vector) {
	o << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")v";
	return (o);
}

Vec	operator*(double n, Vec const &vec) {
	return (vec * n);
} //Vec(vec.x * n, vec.y * n, vec.z *n)
Vec	operator*(Vec const &vec, double n) {
	return (vec * n);
}

Vec	operator*(Vec const &vec, Vec const &vec2) {
	return (Vec(vec.x * vec2.x, vec.y * vec2.y, vec.z * vec2.z));
}

Vec	operator/(double n, Vec const &vec) {
	return (vec / n);
}
Vec	operator/(Vec const &vec, double n) {
	return (vec / n);
}

double	dot(Vec const &vec1, Vec const &vec2) {
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

Vec	cross(Vec const &vec1, Vec const &vec2) {
	return (Vec(vec1.y * vec2.z - vec1.z * vec2.y,
			vec1.z * vec2.x - vec1.x * vec2.z,
			vec1.x * vec2.y - vec1.y * vec2.x));
}
