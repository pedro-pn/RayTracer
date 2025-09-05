#include "RayTracer.hpp"

static Sphere   floor(void) {
    Sphere  floor;

    floor.getTransform().scale(10, 0.01, 10);
    floor.getMaterial().colour = color(1, 0.9, 0.9);
    floor.getMaterial().specular = 0;

    return (floor);
}

static Sphere   leftWall(void) {
    Sphere  leftWall;

    leftWall.getMaterial().colour = color(1, 0.9, 0.9);
    leftWall.getMaterial().specular = 0;
    leftWall.getTransform().scale(10, 0.01, 10)
    .rotateX(M_PI / 2)
    .rotateY(-M_PI / 4)
    .translate(0, 0, 5);

    return (leftWall);
}

static Sphere   rightWall(void) {
    Sphere  rightWall;

    rightWall.getMaterial().colour = color(1, 0.9, 0.9);
    rightWall.getMaterial().specular = 0;
    rightWall.getTransform().scale(10, 0.01, 10)
    .rotateX(M_PI / 2)
    .rotateY(M_PI / 4)
    .translate(0, 0, 5);

    return (rightWall);
}

static Sphere   middleSphere(void) {
    Sphere middleSphere;

    middleSphere.getTransform().scale(0.5, 0.5, 0.5).translate(-0.5, 1, 0.5);
    middleSphere.getMaterial().colour = color(0.1, 1, 0.5);
    middleSphere.getMaterial().diffuse = 0.7;
    middleSphere.getMaterial().specular = 0.3;

    return (middleSphere);
}

static Sphere   rightSphere(void) {
    Sphere rightSphere;

    rightSphere.getTransform().scale(0.5, 0.5, 0.5).translate(1.5, 0.5, -0.5);
    rightSphere.getMaterial().colour = color(0.5, 1, 0.1);
    rightSphere.getMaterial().diffuse = 0.7;
    rightSphere.getMaterial().specular = 0.3;

    return (rightSphere);
}

static Sphere   leftSphere(void) {
    Sphere leftSphere;

    leftSphere.getTransform().scale(0.33, 0.33, 0.33).translate(-1.5, 0.33, -0.75);
    leftSphere.getMaterial().colour = color(1, 0.8, 0.1);
    leftSphere.getMaterial().diffuse = 0.7;
    leftSphere.getMaterial().specular = 0.3;

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
    world.addObject(floor());
    world.addObject(rightWall());
    world.addObject(leftWall());
    world.addObject(middleSphere());
    world.addObject(rightSphere());
    world.addObject(leftSphere());
    
    Canvas image = cam.render(world);

    image.saveToPPM("SpheresDemo.ppm");
}