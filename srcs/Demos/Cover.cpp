#include "RayTracer.hpp"

static t_material   whiteMaterial(void) {
    t_material  m;

    m.colour = color(1, 1, 1);
    m.diffuse = 0.7;
    m.ambient = 0.1;
    m.specular = 0.0;
    m.reflective = 0.1;

    return (m);
}

static t_material   blueMaterial(void) {
    t_material  m = whiteMaterial();

    m.colour = color(0.537, 0.831, 0.914);

    return (m);
}

static t_material   redMaterial(void) {
    t_material  m = whiteMaterial();

    m.colour = color(0.941, 0.322, 0.388);

    return (m);
}

static Matrix   standardTransform(void) {
    Matrix  transform;

    transform.setIdentity();
    transform.scale(0.5, 0.5, 0.5).translate(1, -1, 1);

    return (transform);
}

static Matrix   largeObject(void) {
    Matrix transform = standardTransform();

    transform.scale(3.5, 3.5, 3.5);

    return (transform);
}

static Matrix   mediumObject(void) {
    Matrix transform = standardTransform();

    transform.scale(3, 3, 3);

    return (transform);
}

static Matrix   smallObject(void) {
    Matrix transform = standardTransform();

    transform.scale(2, 2, 2);

    return (transform);
}

static shapePtr background(void) {
    shapePtr    p = make_unique<Plane>();

    p->getMaterial().colour = color(1, 1, 1);
    p->getMaterial().ambient = 1;
    p->getMaterial().diffuse = 0;
    p->getMaterial().specular = 0;
    p->getTransform().rotateX(M_PI / 2).translate(0, 0, 500);

    return (p);
}

static shapePtr ball(void) {
    shapePtr    s = make_unique<Sphere>();

    s->getMaterial().colour = color(0.373, 0.404, 0.550);
    s->getMaterial().ambient = 0;
    s->getMaterial().diffuse = 0.2;
    s->getMaterial().specular = 1.0;
    s->getMaterial().shininess = 200;
    s->getMaterial().reflective = 0.7;
    s->getMaterial().transparency = 0.7;
    s->getMaterial().refractiveIndex = 1.5;

    s->setTransform(largeObject());

    return (s);
}

static t_material   purpleMaterial(void) {
    t_material  m = whiteMaterial();

    m.colour = color(0.373, 0.404, 0.550);

    return (m);
}

static void createCubes(World &world) {
    shapePtr    c1 = make_unique<Cube>();
    shapePtr    c2 = make_unique<Cube>();
    shapePtr    c3 = make_unique<Cube>();
    shapePtr    c4 = make_unique<Cube>();
    shapePtr    c5 = make_unique<Cube>();
    shapePtr    c6 = make_unique<Cube>();
    shapePtr    c7 = make_unique<Cube>();
    shapePtr    c8 = make_unique<Cube>();
    shapePtr    c9 = make_unique<Cube>();
    shapePtr    c10 = make_unique<Cube>();
    shapePtr    c11 = make_unique<Cube>();
    shapePtr    c12 = make_unique<Cube>();
    shapePtr    c13 = make_unique<Cube>();
    shapePtr    c14 = make_unique<Cube>();
    shapePtr    c15 = make_unique<Cube>();
    shapePtr    c16 = make_unique<Cube>();
    shapePtr    c17 = make_unique<Cube>();

    c1->setTransform(mediumObject().translate(4, 0, 0));
    c1->setMaterial(whiteMaterial());

    c2->setTransform(largeObject().translate(8.5, 1.5, -0.5));
    c2->setMaterial(blueMaterial());

    c3->setTransform(largeObject().translate(0, 0, 4));
    c3->setMaterial(redMaterial());

    c4->setTransform(smallObject().translate(4, 0, 4));
    c4->setMaterial(whiteMaterial());

    c5->setTransform(mediumObject().translate(7.5, 0.5, 4));
    c5->setMaterial(purpleMaterial());

    c6->setTransform(mediumObject().translate(-0.25, 0.25, 8));
    c6->setMaterial(whiteMaterial());

    c7->setTransform(largeObject().translate(4, 1, 7.5));
    c7->setMaterial(blueMaterial());

    c8->setTransform(mediumObject().translate(10, 2, 7.5));
    c8->setMaterial(redMaterial());

    c9->setTransform(smallObject().translate(8, 2, 12));
    c9->setMaterial(whiteMaterial());

    c10->setTransform(smallObject().translate(20, 1, 9));
    c10->setMaterial(whiteMaterial());

    c11->setTransform(largeObject().translate(-0.5, -5, 0.25));
    c11->setMaterial(blueMaterial());

    c12->setTransform(largeObject().translate(4, -4, 0));
    c12->setMaterial(redMaterial());

    c13->setTransform(largeObject().translate(8.5, -4, 0));
    c13->setMaterial(whiteMaterial());

    c14->setTransform(largeObject().translate(0, -4, 4));
    c14->setMaterial(whiteMaterial());

    c15->setTransform(largeObject().translate(-0.5, -4.5, 8));
    c15->setMaterial(purpleMaterial());

    c16->setTransform(largeObject().translate(0, -8, 4));
    c16->setMaterial(whiteMaterial());

    c17->setTransform(largeObject().translate(-0.5, -8.5, 8));
    c17->setMaterial(whiteMaterial());

    world.addShape(move(c1));
    world.addShape(move(c2));
    world.addShape(move(c3));
    world.addShape(move(c4));
    world.addShape(move(c5));
    world.addShape(move(c6));
    world.addShape(move(c7));
    world.addShape(move(c8));
    world.addShape(move(c9));
    world.addShape(move(c10));
    world.addShape(move(c11));
    world.addShape(move(c12));
    world.addShape(move(c13));
    world.addShape(move(c14));
    world.addShape(move(c15));
    world.addShape(move(c16));
    world.addShape(move(c17));
}


void    cover(void) {
    Camera  cam(1000, 1000, 0.785);
    World   world;

    cam.setTransform(viewTransformation(
        point(-6, 6, -10),
        point(6, 0, 6),
        vec(-0.45, 1, 0)
    ));
    world.setLight(pointLight(point(50, 100, -50), color(1, 1, 1)));
    world.addShape(background());
    world.addShape(ball());
    createCubes(world);

    
    Canvas image = cam.render(world);

    image.saveToPPM("cover.ppm");
}
