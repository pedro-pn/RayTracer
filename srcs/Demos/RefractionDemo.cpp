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

static shapePtr sky(void) {
    shapePtr    sky = make_unique<Plane>();

    sky->getTransform().rotateX(M_PI / 4).translate(15, 20, 0);
    sky->getMaterial().pattern = make_shared<Gradient>(ColorUtils::rgbToColorTuple(color(4, 138, 186)), ColorUtils::rgbToColorTuple(color(9, 69, 186)));
    sky->getMaterial().pattern->setTransform(scaling(30, 30, 30));
    return (sky);
}

static shapePtr ball(void) {
    shapePtr    ball = make_unique<Sphere>();

    ball->getMaterial().colour = color(0.3, 0.3, 0.3);
    // ball->getMaterial().pattern = make_shared<Stripe>(color(0.5, 0, 0.7), ColorUtils::white());
    // ball->getMaterial().pattern = make_shared<CheckerMap>(color(0.5, 0, 0.7), ColorUtils::white());
    ball->getMaterial().reflective = 0.9;
    ball->getMaterial().transparency = 0.9;
    ball->getMaterial().optShadow = false;
    // ball->getMaterial().pattern->setTransform(scaling(0.2, 0.2, 0.2));
    // ball->getTransform().rotateX(-M_PI / 2);
    return (ball);
}

static shapePtr ball2(void) {
    shapePtr    ball = make_unique<Sphere>();

    ball->getMaterial().colour = color(0.3, 0.3, 0.3);
    // ball->getMaterial().pattern = make_shared<Stripe>(color(0.5, 0, 0.7), ColorUtils::white());
    // ball->getMaterial().pattern = make_shared<CheckerMap>(color(0.5, 0, 0.7), ColorUtils::white());
    ball->getMaterial().reflective = 0.9;
    ball->getMaterial().refractiveIndex = 1.5;
    
    // ball->getMaterial().transparency = 0.9;
    // ball->getMaterial().pattern->setTransform(translation(4, 0, 4));
    ball->getTransform().translate(4, 0, 4);
    return (ball);
}

static shapePtr ball3(void) {
    shapePtr    ball = make_unique<Sphere>();

    ball->getMaterial().colour = color(0.4, 0.5, 0.3);
    // ball->getMaterial().pattern = make_shared<Stripe>(color(0.5, 0, 0.7), ColorUtils::white());
    // ball->getMaterial().pattern = make_shared<CheckerMap>(color(0.5, 0, 0.7), ColorUtils::white());
    // ball->getMaterial().reflective = 0.9;
    ball->getMaterial().refractiveIndex = 1.5;
    
    ball->getMaterial().transparency = 0.5;
    ball->getTransform().translate(-4, 0, 4);
    // ball->getTransform().rotateX(-M_PI / 2);
    return (ball);
}

void    refractionDemo(void) {
    Camera  cam(1920, 1080, M_PI / 3);
    World   world;

    cam.setTransform(viewTransformation(
        point(0, 1, -5),
        point(0, 0, 0),
        vec(0, 1, 0)
    ));
    world.setLight(pointLight(point(0, 10, 2.5), color(1, 1, 1)));
    world.addShape(floor());
    world.addShape(ball());
    world.addShape(ball2());
    world.addShape(ball3());
    world.addShape(sky());
    
    Canvas image = cam.render(world);

    image.saveToPPM("refractionDemo.ppm");
}
