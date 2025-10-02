#pragma once
#include "Shape.hpp"


typedef struct s_bucket {
    shapeList left;
    shapeList right;
}              t_bucket;

class Group: public Shape {
    
    public:
    
    Group();
    ~Group() = default;
    
    Shape const *   operator[](int index) const;
    
    t_intersect intersect(t_ray const &ray) const override;
    Vec         normalAt(Point const &worldPoint) const override;
    BoundingBox boundsOf(void) const override;
    
    void    addChild(shapePtr shape);
    void    makeSubgroup(shapeList &shapes);   
    t_bucket    partitionChildren(void);

    size_t         count(void) const;

    void            divide(size_t threshold = 2);
    
    private:
    
        shapeList   _children;
};

using groupPtr = unique_ptr<Group>;
