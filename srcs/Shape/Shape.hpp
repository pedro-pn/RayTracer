#pragma once

#include "Algebra.hpp"
#include "Ray.hpp"
#include "Material.hpp"
#include "Intersection.hpp"

class Shape {

    public:

        Shape();
        virtual ~Shape();

        bool    operator==(Shape const &rhs) const;
        // Shape   &operator=(Shape const &rhs);

        virtual t_intersect intersect(t_ray const &ray) const = 0;
        virtual Vec         normalAt(Point const &worldPoint) const = 0;

        Matrix const          &getTransform() const;
        Matrix                &getTransform();
        void                   setTransform(Matrix const &transform);
        Point                  getOrigin(void) const;
        t_material            &getMaterial(void);
        t_material const      &getMaterial(void) const;
        void                   setMaterial(t_material const &material);

    private:

        Point     _origin;
        Matrix    _transform;
        t_material  _material;
};

