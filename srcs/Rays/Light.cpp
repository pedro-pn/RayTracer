#include "RayTracer.hpp"

Vec normalAt(Shape const &shape, Point const &worldPoint) {
    Point   objectPoint = shape.getTransform().inverse() * worldPoint;
    Vec     objectNormal = objectPoint - shape.getOrigin();
    Vec     worldNormal = shape.getTransform().inverse().transpose() * objectNormal;
    worldNormal.w = 0;
    return (worldNormal.normalize());
}

Vec reflect(Vec const &incomingRay, Vec const &normal) {
    return (incomingRay - normal * 2 * dot(incomingRay, normal));
}

t_light pointLight(Point const &position, Color const &intensity) {
    return (t_light(position, intensity));
}

Color   lighting(t_material const &material, t_light const &light, Point const &point, Vec const &eyev, Vec const &normalv, bool inShadow) {
   Color    effectiveColor = material.colour * light.intensity;
   Vec      lightVector = (light.position - point).normalize();
   Color    ambient = material.ambient * effectiveColor;
   Color    specular = ColorUtils::black();
   Color    diffuse = ColorUtils::black();

   double   lightDotNormal = dot(lightVector, normalv);
   if (lightDotNormal >= 0 && inShadow == false) {
        diffuse = effectiveColor * material.diffuse * lightDotNormal;
        Vec   reflectVector = reflect(-lightVector, normalv);
        double  reflectDotEye = dot(reflectVector, eyev);
        if (reflectDotEye > 0) {
            double factor = pow(reflectDotEye, material.shininess);
            specular = light.intensity * material.specular * factor;
        }
    }
    return (ambient + diffuse + specular);
}
