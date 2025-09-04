#pragma once

#include "Sphere.hpp"
#include "Algebra.hpp"
#include "Ray.hpp"
#include "Light.hpp"
#include <algorithm>

class World {

    public:

        World();
        ~World();

        t_intersect intersectWorld(t_ray const &ray) const;
        void    setLight(t_light const &light);
        void    addObject(Sphere const &sphere);

        t_light               &getLight(void);
        vector<Sphere>        &getObjects(void);
        t_light const         &getLight(void) const;
        vector<Sphere> const  &getObjects(void) const;

    private:

        vector<Sphere>  _spheres;
        t_light         _light;
};

// MISC

World   defaultWorld(void);
