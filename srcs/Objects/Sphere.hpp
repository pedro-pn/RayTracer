#ifndef SPHERE_HPP
# define SPHERE_HPP

# include "Algebra.hpp"
# include "Material.hpp"

class Sphere {

    public:

        Sphere();
        ~Sphere();

        // bool    operator==(Sphere const &rhs) const;

        Matrix const    &getTransform() const;
        void            setTransform(Matrix const &transform);
        Point           getOrigin(void) const;
        t_material const  &getMaterial(void) const;
        void            setMaterial(t_material const &material);

    private:

        Point     _origin;
        Matrix    _transform;
        t_material  _material;
};

#endif /* SPHERE_HPP */
