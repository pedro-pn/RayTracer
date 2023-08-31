#ifndef TUPLE_HPP
# define TUPLE_HPP

# include <iostream>

using namespace std;

enum eTupleType {
	VECTOR, POINT
};

class Tuple {

	public:

		Tuple();
		Tuple(double x, double y, double z, double w);
		Tuple(Tuple const &rhs);
		~Tuple();

		Tuple	&operator=(Tuple const &rhs);
		// Tuple	&&operator=(Tuple &rhs) noexcept;
		Tuple	operator+(Tuple const &rhs);
		Tuple	operator-(Tuple const &rhs);
		Tuple	operator-();
		Tuple	operator*(double n);
		Tuple	operator/(double n);
		
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

Vec			vector(double x, double y, double z);
Point		point(double x, double y, double z);

Tuple		operator*(double n, Tuple const &vec);
Tuple		operator*(Tuple const &vec, double n);
Tuple		operator/(double n, Tuple const &vec);
Tuple		operator/(Tuple const &vec, double n);
Vec			operator*(Vec const &vec, Vec const &vec2);
Vec			cross(Vec const &vec1, Vec const &vec2);
double		dot(Vec const &vec1, Vec const &vec2);

#endif /* TUPLE_HPP */
