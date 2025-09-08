#pragma once
#include "Algebra.hpp"
#include "Matrix.hpp"
#include "Tuple.hpp"
#include "ColorUtils.hpp"
#include "Canvas.hpp"
#include "Material.hpp"
#include "Sphere.hpp"
#include "World.hpp"
#include "Ray.hpp"
#include "Light.hpp"
#include "Camera.hpp"
#include <vector>
#include <memory>
#include <optional>
#include <algorithm>


typedef struct s_computations {
    double  t;
    Sphere  object;
    Point   point;
    Point   overPoint;
    Vec     eyev;
    Vec     normalv;
    bool    inside;
}               t_computations;

// COMPUTATIONS

t_computations  prepareComputations(t_intersection const &inter, t_ray const &ray);
Color           shadeHit(World const &world, t_computations const &comps);
Color           colorAt(World const &world, t_ray const &ray);
Matrix          viewTransformation(Point const &from, Point const &to, Vec const &up);

// DEMOS

void    clockDemo(void);
void    sphereDemo(void);
void    spheresDemo(void);
