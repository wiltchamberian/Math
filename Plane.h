#ifndef __PLANE_H
#define __PLANE_H

#include "Vector3D.h"

namespace Sun
{
   
    #define   FRONT  1
    #define    BACK  2
    #define    BOTH  FRONT | BACK
    #define    ON  4

    inline bool isSideCross(int side) {
        return (side & BOTH) == BOTH;
    }

    class Plane
    {
    public:
        Plane();
        //面向平面发线方向，三点为逆时针
        Plane(Vector3D& v1,Vector3D& v2,Vector3D& v3);
        ~Plane();
        //normal vector, should always be normalized!
        Vector3D _normal;
        //the directed distance from origin to the plane
        float _directed_dis = 0.0;
        //if the point is in front of the plane,return true,else return false;
        //
        int pointSide(const Vector3D& v) const;
        bool isParell(const Plane& p2) const;
        float distance(const Vector3D& v) const;
    };
}



#endif