#include "Tuple.hpp"

#include <cmath>

Tuple::Tuple() : x(0), y(0), z(0), w(0) {
}

Tuple::Tuple(double x, double y, double z, double w) : x(x), y(y), z(z), w(w) {
}

Tuple::~Tuple() {
}

Tuple::Tuple(Tuple const &rhs) {
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
	this->w = rhs.w;
}

Tuple	&Tuple::operator=(Tuple const &rhs) {
	if (this == &rhs)
		return (*this);
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
	this->w = rhs.w;
	return (*this);
}

Tuple	Tuple::operator+(Tuple const &rhs) {
	double x, y, z, w;

	x = this->x + rhs.x;
	y = this->y + rhs.y;
	z = this->z + rhs.z;
	w = this->w + rhs.w;
	return (Tuple(x, y, z, w));
}

Tuple	Tuple::operator-(Tuple const &rhs) {
	double x, y, z, w;

	x = this->x - rhs.x;
	y = this->y - rhs.y;
	z = this->z - rhs.z;
	w = this->w - rhs.w;
	return (Tuple(x, y, z, w));
}

Tuple	Tuple::operator-() {
	return (Tuple(0, 0, 0, 0) - *this);
}

Tuple	Tuple::operator*(double n) {
	return (Tuple(this->x * n, this->y * n, this->z * n, this->w * n));
}

Tuple	Tuple::operator/(double n) {
	return (Tuple(this->x / n, this->y / n, this->z / n, this->w / n));
}

double	Tuple::magnitude(void) const {
	return (sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2)));
}

Tuple	Tuple::normalize(void) const {
	double	mag;

	mag = this->magnitude();
	return (Tuple(x / mag, y / mag, z / mag, w / mag));
}


// related

ostream&	operator<<(ostream &o, Tuple const &tuple) {
	o << "(" << tuple.x << ", " << tuple.y << ", " << tuple.z << ", " << tuple.w
	<< ")";
	return (o);
}

Tuple	operator*(double n, Tuple const &tuple) {
	return (tuple * n);
} //Vec(vec.x * n, vec.y * n, vec.z *n)
Tuple	operator*(Tuple const &tuple, double n) {
	return (tuple * n);
}

Vec	operator*(Vec const &vec, Vec const &vec2) {
	return (Vec(vec.x * vec2.x, vec.y * vec2.y, vec.z * vec2.z, vec.w * vec2.w));
}

Tuple	operator/(double n, Tuple const &tuple) {
	return (tuple / n);
}
Tuple	operator/(Tuple const &tuple, double n) {
	return (tuple / n);
}

double	dot(Vec const &vec1, Vec const &vec2) {
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z + vec1.w * vec2.w);
}

Vec	cross(Vec const &vec1, Vec const &vec2) {
	return (Vec(vec1.y * vec2.z - vec1.z * vec2.y,
			vec1.z * vec2.x - vec1.x * vec2.z,
			vec1.x * vec2.y - vec1.y * vec2.x, 0));
}

Vec	vector(double x, double y, double z) {
	return (Vec(x, y, z, VECTOR));
}

Point point(double x, double y, double z) {
	return (Point(x, y, z, POINT));
}
