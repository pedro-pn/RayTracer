#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <iostream>
using namespace std;

class Vec {

	public:

		Vec();
		Vec(double x, double y, double z);
		Vec(Vec const &rhs);
		~Vec();

		Vec	&operator=(Vec const &rhs);
		Vec	operator+(Vec const &rhs);
		Vec	operator-(Vec const &rhs);
		Vec	operator-();
		Vec	operator*(double n);
		Vec	operator/(double n);
		
		double	magnitude(void) const;
		Vec		normalize() const;

		double	x;
		double	y;
		double	z;
		double	w;

		friend ostream&	operator<<(ostream &o, Vec const &vector);
};

// Vec	operator-(Vec const &v1, Vec const &v2);
Vec		operator*(double n, Vec const &vec);
Vec		operator*(Vec const &vec, double n);
Vec		operator*(Vec const &vec, Vec const &vec2);
Vec		operator/(double n, Vec const &vec);
Vec		operator/(Vec const &vec, double n);
Vec		cross(Vec const &vec1, Vec const &vec2);
double	dot(Vec const &vec1, Vec const &vec2);

#endif /* VECTOR_HPP */
