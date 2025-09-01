#ifndef SPHERE_HPP
# define SPHERE_HPP


class Sphere {

    public:

        Sphere();
        ~Sphere();

        // bool    operator==(Sphere const &rhs) const;

        Matrix const  &getTransform() const;
        void    setTransform(Matrix const &transform);

    private:

        Point   _origin;
        Matrix  _transform;
};

#endif /* SPHERE_HH */
