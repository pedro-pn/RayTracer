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

Vec             reflect(Vec const &incomingRay, Vec const &normal);
t_light         pointLight(Point const &position, Color const &intensity);
Color           lighting(Shape const &shape, t_light const &light, Point const &point, Vec const &eyev, Vec const &normalv, bool inShadow);
