/*****************************************************************************
* @brief : brief
* @author : acedtang
* @date : 2021/3/23
* @version : ver 1.0
* @inparam : 
* @outparam : 
*****************************************************************************/

#ifndef __BOX_H
#define __BOX_H

#include "Vector3D.h"
#include "Ray.h"

namespace Sun {

    struct Box {
        Vector3D mins_;
        Vector3D maxs_;
    };

    class AABB :public Box{
    public:
        AABB();
        AABB(const Vector3D& a, const Vector3D& b);

        Vector3D center() const;

        bool hit(const Ray& r, float tmin, float tmax) const;
        //another for glsl optimize
        bool hit2(const Ray& r, float tmin, float tmax) const;
        //surroundingBox
        static AABB surroundingBox(const AABB& box1, const AABB& box2);
    };
}

#endif