#pragma once

#include "Ray.hpp"
#include "Shape.hpp"
#include "Light.hpp"
#include "Intersection.hpp"
#include <memory>

class World {

    public:

        World();
        ~World();

        World(const World &) = delete;
        World&  operator=(const World&) = delete;

        World(World&&) noexcept = default;
        World& operator=(World&&) noexcept = default;

        t_intersect     intersectWorld(t_ray const &ray) const;
        void            setLight(t_light const &light);
        void            addShape(shapePtr shape);
        bool            isShadowed(Point const &point) const;

        t_light         &getLight(void);
        t_light const   &getLight(void) const;
        shapeList       &getShapes(void);
        shapeList const &getShapes(void) const;

    private:

        shapeList       _shape;
        t_light         _light;
};

// MISC

World   defaultWorld(void);
