#ifndef TUPLE_HPP
# define TUPLE_HPP

# include <iostream>

using namespace std;

enum eTupleType {
	VECTOR, POINT, COLOR = 0
};

class Tuple {

	public:

		Tuple();
		Tuple(double x, double y, double z, double w);
		Tuple(Tuple const &rhs);
		~Tuple();

		Tuple	&operator=(Tuple const &rhs);
		// Tuple	&&operator=(Tuple &rhs) noexcept;
		Tuple	operator+(Tuple const &rhs) const;
		Tuple	operator-(Tuple const &rhs) const;
		Tuple	operator-() const;
		Tuple	operator*(double n) const;
		Tuple	operator/(double n) const;
		bool	operator==(Tuple const &rhs) const;
		
		double		magnitude(void) const;
		Tuple		normalize() const;

		double	x;
		double	y;
		double	z;
		double	w;

		friend ostream&	operator<<(ostream &o, Tuple const &vector);
};

using Vec = Tuple;
using Point = Tuple;
using Color = Tuple;

Vec			vec(double x, double y, double z);
Point		point(double x, double y, double z);
Color		color(double red, double green, double z);

Tuple		operator*(double n, Tuple &Tuple);
Tuple		operator*(Tuple const &tuple, Tuple const &tuple2);
Vec			cross(Vec const &vec1, Vec const &vec2);
double		dot(Vec const &vec1, Vec const &vec2);

#endif /* TUPLE_HPP */
