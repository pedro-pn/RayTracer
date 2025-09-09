#include "RayTracer.hpp"

static  shapePtr    floor(void) {
    shapePtr    floor = make_unique<Plane>();

    floor->getTransform().rotateX(-M_PI / 2.0);
    floor->getMaterial().colour = color(1, 1, 1);

    return (floor);
}

static shapePtr ball(void) {
    shapePtr    ball = make_unique<Sphere>();

    ball->getMaterial().colour = color(0, 0, 1);

    return (ball);
}

void    planeDemo(void) {
    Camera  cam(250, 250, M_PI / 3);
    World   world;

    cam.setTransform(viewTransformation(
        point(0, 1, -5),
        point(0, 0, 1),
        vec(0, 1, 0)
    ));
    world.setLight(pointLight(point(-10, 5, -10), color(1, 1, 1)));
    world.addShape(floor());
    world.addShape(ball());
    
    Canvas image = cam.render(world);

    image.saveToPPM("PlaneDemo.ppm");
}