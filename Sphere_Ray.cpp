#include "Sphere_Ray.h"


namespace Sun {

    float hit(const Sphere& sphere, const Ray& ray) {
        Vector3D oc = ray.origin_ - sphere.center_;
        float A = ray.direction_.dotProduct(ray.direction_);
        float B = 2 * ray.direction_.dotProduct(oc);
        float C = oc.dotProduct(oc) - sphere.radius_ * sphere.radius_;
        float discriminant = B * B - 4 * A * C;
        if (discriminant < 0) {
            return -1.;
        }
        return (-B - sqrt(discriminant)) / (2 * A);
    }

}