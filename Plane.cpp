#include "Plane.h"

namespace Sun {

    Plane::Plane()
    {

    }

    Plane::~Plane()
    {

    }

    //面向平面发线方向，三点为逆时针
    Plane::Plane(Vector3D& v1, Vector3D& v2, Vector3D& v3)
    {
        _normal = (v2 - v1).crossProduct(v3 - v1);
        _normal.normalize();
        _directed_dis = v1.dotProduct(_normal);
    }

    int Plane::pointSide(const Vector3D& v) const
    {
        if (equal(_directed_dis, 0.)) {
            float c = v.dotProduct(_normal);
            if (c > 0)return FRONT;
            else if (c < 0) return BACK;
            else return ON;
        }
        Vector3D v_plane = _normal * _directed_dis;

        Vector3D v_ = v - v_plane;
        float c = v_.dotProduct(v_plane);
        if (_directed_dis > 0) {
            if (c > 0)
                return FRONT;
            else if (c < 0)
                return BACK;
            else
                return ON;
        }
        else {
            if (c > 0)
                return BACK;
            else if (c < 0)
                return FRONT;
            else
                return ON;
        }
        return ON;
    }

    bool Plane::isParell(const Plane& p2) const
    {
        return parallel(_normal, p2._normal);
    }

    float Plane::distance(const Vector3D& v) const
    {
        Vector3D v_plane = _normal * _directed_dis;
        Vector3D v_ = v - v_plane;
        float d = v_.dotProduct(_normal);
        d = d < 0 ? (-d) : d;
        return d;
    }
}

