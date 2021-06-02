/*****************************************************************************
* @brief : Sphere
* 3Œ¨«ÚÃÂ¿‡
* @author : acedtang
* @date : 2021/4/26
* @version : ver 1.0
* @inparam :
* @outparam :
*****************************************************************************/

#ifndef __SPHERE_H
#define __SPHERE_H

#include "Vector3D.h"

namespace Sun {

    class Sphere {
    public:
        Sphere();
        Sphere(const Vector3D& center, float r);
        
        Vector3D& center();
        float& radius();

        Vector3D center_;
        float    radius_;
    };

}

#endif