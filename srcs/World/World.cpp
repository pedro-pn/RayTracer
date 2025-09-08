#include "World.hpp"
#include "Sphere.hpp"
#include <algorithm>

World::World() {
}

World::~World() {
}

t_intersect World::intersectWorld(t_ray const &ray) const {
    t_intersect xs;

    xs.count = 0;
    for (auto it = _shape.begin(); it != _shape.end(); it++) {
        xs += (*it)->intersect(ray);
    }
    sort(xs.intersections.begin(), xs.intersections.end());
    return (xs);
}

void    World::setLight(t_light const &light) { 
    this->_light = light;
}

void    World::addShape(shapePtr shape) {
    this->_shape.push_back(move(shape));
}

t_light         &World::getLight(void) {
    return (this->_light);
}

shapeList  &World::getShapes(void) {
    return (this->_shape);
}

t_light const   &World::getLight(void) const {
    return (this->_light);
}

shapeList const  &World::getShapes(void) const {
    return (this->_shape);
}

bool    World::isShadowed(Point const &point) const {
    Vec v = this->_light.position - point;
    Vec direction = v.normalize();
    double distance = v.magnitude();

    t_ray r = ray(point, direction);
    t_intersect xs = this->intersectWorld(r);
    auto inter = hit(xs);

    if (inter == nullopt)
        return (false);
    if ((*inter).t < distance)
        return (true);
    return (false);
}

World   defaultWorld(void) {
    t_light light = pointLight(point(-10, 10, -10), color(1, 1, 1));
    shapePtr  s1 = make_unique<Sphere>();
    shapePtr  s2 = make_unique<Sphere>();
    t_material  m = t_material();
    World   world;

    m.colour = color(0.8, 1.0, 0.6);
    m.diffuse = 0.7;
    m.specular = 0.2;
    s1->setMaterial(m);
    s2->setTransform(Matrix().setIdentity().scale(0.5, 0.5, 0.5));
    world.setLight(light);
    world.addShape(move(s1));
    world.addShape(move(s2));
    return (world);
}

