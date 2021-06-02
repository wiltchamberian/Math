#include "Ray.h"

namespace Sun {
    Ray::Ray() {

    }

    Ray::Ray(const Vector3D& origin, const Vector3D& direction, float time)
        :origin_(origin)
        ,direction_(direction)
        ,time_(time)
    {

    }

    Vector3D& Ray::origin() {
        return origin_;
    }

    Vector3D& Ray::direction() {
        return direction_;
    }

    Vector3D Ray::pointAt(float t) const {
        return origin_ + direction_ * t;
    }

}