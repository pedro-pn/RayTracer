#ifndef POINT_HPP
# define POINT_HPP

# include <iostream>
# include "Vec.hpp"

class Vec;

using namespace std;

class Point {

	public:

		Point(double x, double y, double z);
		Point(Point const &rhs);
		~Point();

		Point	&operator=(Point const &rhs);

		double	x;
		double	y;
		double	z;
		double	w;

		friend ostream&	operator<<(ostream &o, Point const &point);
		
};

Vec		operator-(Point const &p1, Point const &p2);
Point	operator-(Point const &p, Vec const &v);
Point	operator*(Point const &p, double n);
Point	operator*(double n, Point const &p);
Point	operator/(Point const &p, double n);

#endif /* POINT_HPP */
