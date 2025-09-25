#pragma once

#include "Algebra.hpp"
#include "Ray.hpp"
#include "Material.hpp"
#include "Intersection.hpp"

using shapeList = vector<unique_ptr<Shape>>;
using shapePtr = unique_ptr<Shape>;

class Group;

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
        t_material            &getMaterial(void);
        t_material const      &getMaterial(void) const;
        void                   setMaterial(t_material const &material);
        Color                  patternAt(Point const &patternPoint) const;
        void                   setParent(Group const *group);
        Group   const          *getParent(void) const;

        
        private:
        
        Matrix      _transform;
        t_material  _material;
        
        protected:
        
        Vec            _normalToWorld(Vec const &normal) const;
        Point          _worldToObject(Point const &p) const;

        Group   const *_parent;
};
