#ifndef RAYTRACER_HPP
# define RAYTRACER_HPP

# include "algebra.hpp"
# include "../srcs/Algebra/Matrix.hpp"
# include "../srcs/Algebra/Tuple.hpp"
# include "../srcs/Canvas/ColorUtils.hpp"
# include "../srcs/Canvas/Canvas.hpp"
# include "Sphere.hpp"
# include <vector>
# include <memory>
# include <optional>
# include <algorithm>

// RAY

typedef struct s_ray {
    Point   origin;
    Vec     direction;
}           t_ray;

typedef struct s_intersection {
    double  t;
    Sphere const *object;

    bool    operator==(struct s_intersection const &rhs) const {
        return (this->t == rhs.t && this->object == rhs.object);
    }
    bool    operator<(struct s_intersection const &rhs) const {
        return (this->t < rhs.t);
    }
    bool    operator>(struct s_intersection const &rhs) const {
        return (this->t > rhs.t);
    }
}               t_intersection;

typedef struct s_intersect {
    int                     count;
    vector<t_intersection>  intersections;
}               t_intersect;

t_ray           ray(Point const &origin, Vec const &direction);
Point           position(t_ray const &ray, double t);
t_intersect     intersect(Sphere const *s, t_ray const &r);
t_intersection  intersection(double t, Sphere const *s);
optional<t_intersection>    hit(t_intersect &xs);
t_ray           transformRay(t_ray const &r, Matrix const &transform);

// DEMOS

void    clockDemo(void);
void    sphereDemo(void);

#endif
