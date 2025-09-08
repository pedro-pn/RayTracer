#include "RayTracer.hpp"

static shapePtr   floor(void) {
    shapePtr  floor = make_unique<Sphere>();

    floor->getTransform().scale(10, 0.01, 10);
    floor->getMaterial().colour = color(1, 0.9, 0.9);
    floor->getMaterial().specular = 0;

    return (floor);
}

static shapePtr   leftWall(void) {
    shapePtr  leftWall = make_unique<Sphere>();

    leftWall->getMaterial().colour = color(1, 0.9, 0.9);
    leftWall->getMaterial().specular = 0;
    leftWall->getTransform().scale(10, 0.01, 10)
    .rotateX(M_PI / 2)
    .rotateY(-M_PI / 4)
    .translate(0, 0, 5);

    return (leftWall);
}

static shapePtr   rightWall(void) {
    shapePtr  rightWall = make_unique<Sphere>();

    rightWall->getMaterial().colour = color(1, 0.9, 0.9);
    rightWall->getMaterial().specular = 0;
    rightWall->getTransform().scale(10, 0.01, 10)
    .rotateX(M_PI / 2)
    .rotateY(M_PI / 4)
    .translate(0, 0, 5);

    return (rightWall);
}

static shapePtr   middleSphere(void) {
    shapePtr middleSphere = make_unique<Sphere>();

    middleSphere->getTransform().translate(-0.5, 1, 0.5).scale(0.5, 0.5, 0.5);
    middleSphere->getMaterial().colour = color(0.1, 1, 0.5);
    middleSphere->getMaterial().diffuse = 0.7;
    middleSphere->getMaterial().specular = 0.3;

    return (middleSphere);
}

static shapePtr   rightSphere(void) {
    shapePtr rightSphere = make_unique<Sphere>();

    rightSphere->getTransform().scale(0.5, 0.5, 0.5).translate(1.5, 0.5, -0.5);
    rightSphere->getMaterial().colour = color(0.5, 1, 0.1);
    rightSphere->getMaterial().diffuse = 0.7;
    rightSphere->getMaterial().specular = 0.3;

    return (rightSphere);
}

static shapePtr   leftSphere(void) {
    shapePtr leftSphere = make_unique<Sphere>();

    leftSphere->getTransform().scale(0.33, 0.33, 0.33).translate(-1.5, 0.33, -0.75);
    leftSphere->getMaterial().colour = color(1, 0.8, 0.1);
    leftSphere->getMaterial().diffuse = 0.7;
    leftSphere->getMaterial().specular = 0.3;

    return (leftSphere);
}

void    spheresDemo(void) {
    Camera  cam(1000, 500, M_PI / 3);
    World   world;

    cam.setTransform(viewTransformation(
        point(0, 1.5, -5),
        point(0, 1, 0),
        vec(0, 1, 0)
    ));
    world.setLight(pointLight(point(-10, 10, -10), color(1, 1, 1)));
    world.addShape(floor());
    world.addShape(rightWall());
    world.addShape(leftWall());
    world.addShape(middleSphere());
    world.addShape(rightSphere());
    world.addShape(leftSphere());
    
    Canvas image = cam.render(world);

    image.saveToPPM("SpheresDemo.ppm");
}