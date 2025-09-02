#include "RayTracer.hpp"

void    sphereDemo(void) {
    Canvas canva(500, 500);
    double  wallSize = 20;
    double  wall_z = 7;
    double  world_x;
    double  world_y;
    double  half;
    double  pixel_size;
    Sphere  *s = new Sphere();
    Point   origin = point(0, 0, -5);
    
    pixel_size = wallSize / canva.getHeight();
    half = wallSize / 2;
    for (int i = 0; i < canva.getWidth(); i++) {
        world_x = (pixel_size * i) - half;
        for (int j = 0; j < canva.getHeight(); j++) {
            world_y = half - (pixel_size * j );
            t_ray r = ray(origin, point(world_x, world_y, wall_z) - origin);
            t_intersect xs = intersect(s, r);
            if (xs.count > 0) {
                auto inter = hit(xs);
                if (inter != nullopt) {
                    canva.writePixel(i, j, color(255, 255, 255));
                }
            }
            
        }
    }
    canva.saveToPPM("sphere.ppm");
    delete s;
}