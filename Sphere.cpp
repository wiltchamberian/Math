#include "Sphere.h"

namespace Sun {

    Sphere::Sphere() {

    }

    Sphere::Sphere(const Vector3D& center, float r)
        :center_(center)
        ,radius_(r)
    {


    }

    Vector3D& Sphere::center() {
        return center_;
    }

    float& Sphere::radius() {
        return radius_;
    }
}