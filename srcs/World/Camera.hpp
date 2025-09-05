#pragma once

#include "RayTracer.hpp"

class Camera {

    public:

        Camera(int hsize, int vsize, double fieldOfView);
        ~Camera();

		double hsize;
		double vsize;
		double  fieldOfView;
		double  halfView;
		double  halfWidth;
		double  halfHeight;
		double  pixelSize;
		

		void	setTransform(Matrix const &transform);
        Matrix  const &getTransform() const;
		t_ray	rayForPixel(int px, int py) const;
		Canvas	render(World const &world) const;
		
	private:
		
       	Matrix  _transform;
        
};