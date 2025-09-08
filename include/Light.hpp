#pragma once

#include "Algebra.hpp"


// LIGHT

typedef struct s_light {
    Point   position;
    Color   intensity;
    s_light() {};
    s_light(Point const &position, Color const &intensity) : position(position), intensity(intensity) {}

    bool    operator==(s_light const &rhs) const {
        return (this->position == rhs.position && this->intensity == rhs.intensity);
    }
}           t_light;

Vec             normalAt(Sphere const &object, Point const &worldPoint);
Vec             reflect(Vec const &incomingRay, Vec const &normal);
t_light         pointLight(Point const &position, Color const &intensity);
Color           lighting(t_material const &material, t_light const &light, Point const &point, Vec const &eyev, Vec const &normalv, bool inShadow);