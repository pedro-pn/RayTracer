#include "RayTracer.hpp"

Vec reflect(Vec const &incomingRay, Vec const &normal) {
    return (incomingRay - normal * 2 * dot(incomingRay, normal));
}

t_light pointLight(Point const &position, Color const &intensity) {
    return (t_light(position, intensity));
}

Color   lighting(Shape const &shape, t_light const &light, Point const &point, Vec const &eyev, Vec const &normalv, bool inShadow) {
    Color    effectiveColor;
    if (shape.getMaterial().pattern)
        effectiveColor = shape.patternAt(point) * light.intensity;
    else
        effectiveColor = shape.getMaterial().colour * light.intensity;
        
    Vec      lightVector = (light.position - point).normalize();
    Color    ambient = shape.getMaterial().ambient * effectiveColor;
    Color    specular = ColorUtils::black();
    Color    diffuse = ColorUtils::black();

   double  lightDotNormal = dot(lightVector, normalv);
   if (lightDotNormal >= EPSILON && inShadow == false) {
        diffuse = effectiveColor * shape.getMaterial().diffuse * lightDotNormal;
        Vec   reflectVector = reflect(-lightVector, normalv);
        double  reflectDotEye = dot(reflectVector, eyev);
        if (reflectDotEye > EPSILON) {
            double factor = pow(reflectDotEye, shape.getMaterial().shininess);
            specular = light.intensity * shape.getMaterial().specular * factor;
        }
    }
    return (ambient + diffuse + specular);
}
