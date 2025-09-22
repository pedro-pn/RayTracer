#include "RayTracer.hpp"

static  shapePtr    floor(void) {
    shapePtr    floor = make_unique<Plane>();

    floor->getTransform().translate(0, -1, 0);
    floor->getMaterial().colour = color(1, 1, 1);
    floor->getMaterial().reflective = 0.3;
    floor->getMaterial().pattern = make_shared<Checker>(ColorUtils::white(), ColorUtils::rgbToColorTuple(color(0, 162, 232)));
    floor->getMaterial().pattern->getTransform().rotateY(M_PI / 4);

    return (floor);
}

static shapePtr wall(void) {
    shapePtr    wall = make_unique<Plane>();

    wall->getTransform().rotateX(M_PI / 4).translate(15, 20, 0);
    wall->getMaterial().pattern = make_shared<Gradient>(ColorUtils::rgbToColorTuple(color(168, 166, 152)), ColorUtils::rgbToColorTuple(color(168, 103, 156)));
    wall->getMaterial().pattern->setTransform(scaling(30, 30, 30));
    return (wall);
}

static shapePtr ball(void) {
    shapePtr    ball = make_unique<Sphere>();

    ball->getMaterial().colour = color(0, 0, 1);
    // ball->getMaterial().pattern = make_shared<Stripe>(color(0.5, 0, 0.7), ColorUtils::white());
    ball->getMaterial().pattern = make_shared<CheckerMap>(color(0.5, 0, 0.7), ColorUtils::white());
    ball->getMaterial().reflective = 0.2;
    // ball->getMaterial().pattern->setTransform(scaling(0.2, 0.2, 0.2));
    // ball->getTransform().rotateX(-M_PI / 2);
    return (ball);
}

void    testDemo(void) {
    Camera  cam(1920, 1080, M_PI / 3);
    World   world;

    cam.setTransform(viewTransformation(
        point(0, 1, -5),
        point(0, 0, 0),
        vec(0, 1, 0)
    ));
    world.setLight(pointLight(point(-10, 10, -10), color(1, 1, 1)));
    world.addShape(floor());
    world.addShape(ball());
    world.addShape(wall());
    
    Canvas image = cam.render(world);

    image.saveToPPM("testDemo.ppm");
}
