#pragma once
#include "Algebra.hpp"
#include "Matrix.hpp"
#include "Tuple.hpp"
#include "ColorUtils.hpp"
#include "Canvas.hpp"
#include "Material.hpp"
#include "Sphere.hpp"
#include "Cube.hpp"
#include "Plane.hpp"
#include "Cylinder.hpp"
#include "Cone.hpp"
#include "Group.hpp"
#include "World.hpp"
#include "Ray.hpp"
#include "Light.hpp"
#include "Camera.hpp"
#include "Intersection.hpp"
#include "Stripe.hpp"
#include "Gradient.hpp"
#include "Checker.hpp"
#include "Ring.hpp"
#include <vector>
#include <memory>
#include <optional>
#include <algorithm>

#define REMAINING 4

typedef struct s_computations {
    double        t;
    Shape const  *shape;
    Point         point;
    Point         overPoint;
    Point         underPoint;
    Vec           eyev;
    Vec           normalv;
    bool          inside;
    Vec           reflectv;
    double        n1;
    double        n2;
}               t_computations;

// COMPUTATIONS

t_computations  prepareComputations(t_intersection const &inter, t_ray const &ray, t_intersect &xs);
Color           shadeHit(World const &world, t_computations const &comps, int remaining);
Color           colorAt(World const &world, t_ray const &ray, int remaining);
Matrix          viewTransformation(Point const &from, Point const &to, Vec const &up);
Color           reflectedColor(World const &world, t_computations const &comps, int remaining);
Color           refractedColor(World const &world, t_computations const &comps, int remaining);
double          schlick(t_computations const &comps);

// DEMOS

void    clockDemo(void);
void    sphereDemo(void);
void    spheresDemo(void);
void    planeDemo(void);
void    testDemo(void);
void    refractionDemo(void);
void    cubeDemo(void);
void    cover(void);
void    groupDemo(void);
