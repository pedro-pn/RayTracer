#pragma once

#include "Algebra.hpp"
#include "ColorUtils.hpp"
#include "Pattern.hpp"
#include <memory>

using patternPtr = shared_ptr<Pattern>;

// Material

typedef struct s_material {
    Color       colour;
    patternPtr  pattern;
    double      ambient;
    double      diffuse;
    double      specular;
    double      shininess;
    double      reflective;
    double      transparency;
    double      refractiveIndex;

    s_material() : colour(color(1, 1, 1)),
                    pattern(nullptr),
                    ambient(0.1),
                    diffuse(0.9),
                    specular(0.9),
                    shininess(200.0),
                    reflective(0.0),
                    transparency(0),
                    refractiveIndex(1.0) {}
    bool    operator==(struct s_material const &rhs) const {
        return (this->colour == rhs.colour && 
            this->ambient == rhs.ambient &&
            this->diffuse == rhs.diffuse &&
            this->specular == rhs.specular &&
            this->shininess == rhs.shininess
        );
    }
}               t_material;
