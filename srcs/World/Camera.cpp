#include "Camera.hpp"
#include <cmath>

Camera::Camera(int hsize, int vsize, double fieldOfView) : hsize(hsize), vsize(vsize), fieldOfView(fieldOfView) {
    double  aspect;
    this->halfView = tan(this->fieldOfView / 2.0);
    aspect = this->hsize / this->vsize;

    if (aspect >= 1) {
        this->halfWidth = this->halfView;
        this->halfHeight = this-> halfView / aspect;
    } else {
        this->halfWidth = this->halfView * aspect;
        this->halfHeight = this-> halfView;
    }
    this->pixelSize = (this->halfWidth  * 2.0) / this->hsize;
    this->_transform = Matrix().setIdentity();
}

Camera::~Camera() {
}

Matrix const    &Camera::getTransform(void) const {
    return (this->_transform);
}

void    Camera::setTransform(Matrix const &transform) {
    this->_transform = transform;
}

t_ray   Camera::rayForPixel(int px, int py) const {
    double  xoffset = (px + 0.5) * this->pixelSize;
    double  yoffset = (py + 0.5) * this->pixelSize;
    double  worldX = this->halfWidth - xoffset;
    double  worldY = this->halfHeight - yoffset;

    Point   pixel = this->_transform.inverse() * point(worldX, worldY, -1);
    Point   origin = this->_transform.inverse() * point(0, 0, 0);
    Point   direction = (pixel - origin).normalize();

    return (ray(origin, direction));
}

Canvas  Camera::render(World const &world) const {
    Canvas  image(this->hsize, this->vsize);
    
    for (int y = 0; y < this->vsize; y++) {
        for (int x = 0; x < this->hsize; x++) {
            t_ray   ray = this->rayForPixel(x, y);
            Color   color = colorAt(world, ray, REMAINING);
            image.writePixel(x, y, color);
        }
    }

    return (image);
}
