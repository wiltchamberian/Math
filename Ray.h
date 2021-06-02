/*****************************************************************************
* @brief : Ray
* …‰œﬂ
* @author : acedtang
* @date : 2021/4/26
* @version : ver 1.0
* @inparam :
* @outparam :
*****************************************************************************/

#ifndef __RAY_H
#define __RAY_H

#include "Vector3D.h"

namespace Sun {

    class Ray {
    public:
        Ray();
        Ray(const Vector3D& origin, const Vector3D& direction, float time = 0.f);
        Vector3D& origin();
        Vector3D& direction();
        Vector3D pointAt(float t) const;
        Vector3D origin_;
        Vector3D direction_;

        float time_;
    };

}


#endif