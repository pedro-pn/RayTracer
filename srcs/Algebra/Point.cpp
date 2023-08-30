#include "Point.hpp"

Point::Point(double x, double y, double z) : x(x), y(y), z(z), w(1) {
}

Point::~Point() {
}

Point::Point(Point const &rhs) {
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
	this->w = rhs.w;
}

Point	&Point::operator=(Point const &rhs) {
	if (this == &rhs)
		return (*this);
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
	this->w = rhs.w;
	return (*this);
}


ostream&	operator<<(ostream &o, Point const &point) {
	o << "(" << point.x << ", " << point.y << ", " << point.z << ")v";
	return (o);
}

Vec	operator-(Point const &p1, Point const &p2) {
	return (Vec(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z));
};

Point	operator-(Point const &p, Vec const &v) {
	return (Point(p.x - v.x, p.y - v.y, p.z - v.z));
}

Point	operator*(Point const &p, double n) {
	return (Point(p.x * n, p.y * n, p.z * n));
}

Point	operator*(double n, Point const &p) {
	return (p * n);
}

Point	operator/(Point const &p, double n) {
	return (Point(p.x / n, p.y / n, p.z / n));
}
