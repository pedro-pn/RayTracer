#include "RayTracer.hpp"

static shapePtr hexagonCorner(void) {
    shapePtr    corner = make_unique<Sphere>();

    corner->setTransform(translation(0, 0, -1) * scaling(0.25, 0.25, 0.25));
    
    return (corner);
}

static shapePtr hexagonEdge(void) {
    shapePtr    edge = make_unique<Cylinder>();

    dynamic_cast<Cylinder *>(&*edge)->setMaximum(1);
    dynamic_cast<Cylinder *>(&*edge)->setMinimum(0);
    edge->setTransform(translation(0, 0, -1) * rotationY(-M_PI / 6) * rotationZ(-M_PI / 2) * scaling(0.25, 1, 0.25));

    return (edge);
}

static shapePtr hexagonSide(void) {
    shapePtr    side = make_unique<Group>();

     dynamic_cast<Group *>(&*side)->addChild(hexagonCorner());
     dynamic_cast<Group *>(&*side)->addChild(hexagonEdge());

     return (side);
}

static shapePtr hexagon(void) {
    shapePtr    hex = make_unique<Group>();
    shapePtr    side;

    for (int n = 0; n < 6; n++) {
        side = hexagonSide();
        side->setTransform(rotationY(n * M_PI / 3));
        dynamic_cast<Group *>(&*hex)->addChild(move(side));
    }

    return (hex);
}

void    groupDemo(void) {
    Camera  cam(500, 500, M_PI / 3);
    World   world;

    cam.setTransform(viewTransformation(
        point(0, 1, -5),
        point(0, 0, 0),
        vec(0, 1, 0)
    ));
    world.setLight(pointLight(point(-10, 10, -10), color(1, 1, 1)));
    world.addShape(hexagon());
    world.getShapes()[0]->setTransform(rotationX(M_PI / 2));

    
    Canvas image = cam.render(world);

    image.saveToPPM("hexagon.ppm");
}
