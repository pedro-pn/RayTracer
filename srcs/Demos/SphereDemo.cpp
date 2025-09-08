#include "RayTracer.hpp"

void    sphereDemo(void) {
    Canvas canva(500, 500);
    double  wallSize = 10;
    double  wall_z = 7;
    double  world_x;
    double  world_y;
    double  half;
    double  pixel_size;
    Sphere  s = Sphere();
    Point   origin = point(0, 0, -5);
    t_material  m = t_material();
    t_light light = pointLight(point(-10, 10, -10), color(1, 1, 1));
    m.colour = color(1, 0.2, 1);
    s.setMaterial(m);
    pixel_size = wallSize / canva.getHeight();
    half = wallSize / 2;
    for (int i = 0; i < canva.getWidth(); i++) {
        world_x = (pixel_size * i) - half;
        for (int j = 0; j < canva.getHeight(); j++) {
            world_y = half - (pixel_size * j );
            t_ray r = ray(origin, (point(world_x, world_y, wall_z) - origin).normalize());
            t_intersect xs = intersect(s, r);
            if (xs.count > 0) {
                auto inter = hit(xs);
                Point   p = position(r, inter->t);
                Vec     normal = normalAt(inter->object, p);
                Vec     eye = -r.direction;
                if (inter != nullopt) {
                    canva.writePixel(i, j, lighting(inter->object.getMaterial(), light, p, eye, normal, false));
                }
            }
        }
    }
    canva.saveToPPM("sphere.ppm");
}