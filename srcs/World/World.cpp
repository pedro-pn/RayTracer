#include "World.hpp"

World::World() {
}

World::~World() {
}

t_intersect World::intersectWorld(t_ray const &ray) const {
    t_intersect xs;

    xs.count = 0;
    for (auto it = _spheres.begin(); it != _spheres.end(); it++) {
        xs += intersect(*it, ray);
    }
    sort(xs.intersections.begin(), xs.intersections.end());
    return (xs);
}

void    World::setLight(t_light const &light) { 
    this->_light = light;
}
void    World::addObject(Sphere const &sphere) {
    this->_spheres.push_back(sphere);
}

t_light         &World::getLight(void) {
    return (this->_light);
}

vector<Sphere>  &World::getObjects(void) {
    return (this->_spheres);
}

t_light const   &World::getLight(void) const {
    return (this->_light);
}

vector<Sphere> const  &World::getObjects(void) const {
    return (this->_spheres);
}

World   defaultWorld(void) {
    t_light light = pointLight(point(-10, 10, -10), color(1, 1, 1));
    Sphere  s1 = Sphere();
    Sphere  s2 = Sphere();
    t_material  m = t_material();
    World   world;

    m.colour = color(0.8, 1.0, 0.6);
    m.diffuse = 0.7;
    m.specular = 0.2;
    s1.setMaterial(m);
    s2.setTransform(Matrix().setIdentity().scale(0.5, 0.5, 0.5));
    world.setLight(light);
    world.addObject(s1);
    world.addObject(s2);
    return (world);
}

