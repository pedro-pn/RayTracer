#include "RayTracer.hpp"

void    clockDemo(void) {
    Canvas canva(500, 500);

    Point clock;

    for (int hour = 0; hour < 60; hour++) {
        clock = point(0, 100, 0);
        clock = rotationZ(hour * (M_PI/30)) * clock;
        canva.writePixel(clock.x + 250, clock.y + 250, color(255, 255, 255));
    }

    canva.saveToPPM("clock.ppm");
}
