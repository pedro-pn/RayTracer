#pragma once

#include "Algebra.hpp"
#include "ColorUtils.hpp"

// Material

typedef struct s_material {
    Color   colour;
    double  ambient;
    double  diffuse;
    double  specular;
    double  shininess;

    s_material() : colour(color(1, 1, 1)), ambient(0.1), diffuse(0.9), specular(0.9), shininess(200.0) {}
    bool    operator==(struct s_material const &rhs) const {
        return (this->colour == rhs.colour && 
            this->ambient == rhs.ambient &&
            this->diffuse == rhs.diffuse &&
            this->specular == rhs.specular &&
            this->shininess == rhs.shininess
        );
    }
}               t_material;
