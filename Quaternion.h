#ifndef QUATERNION_H
#define QUATERNION_H

#include "Vector3D.h"

/**
 * @brief         Quaternion class.
 * @author        YangWC  
 * @date          2019-05-03 
 * @revised by    Acedtang 2021-01-18
 */

namespace Sun
{
    class Matrix4x4;
    class Quaternion
    {
    public:
        typedef float scalar;
        scalar x = 0.0;
        scalar y = 0.0;
        scalar z = 0.0;
        scalar w = 1.0;

        Quaternion();
        Quaternion(scalar w);
        //构建四元数w+xi+yj+zk
        Quaternion(scalar x, scalar y, scalar z, scalar w);
        //用三维向量构造四元数
        Quaternion(const Vector3D& v);
        ~Quaternion() = default;

        void set(float x, float y, float z, float w);
        void setRotateAxisAndRadius(const Vector3D& v, double radius);

        double length() const;
        double getLength() const;
        double getLengthSquare() const;
        void normalize();
        Quaternion getNormalize() const;
        void inverse();
        Quaternion getInverse() const;
        void conjugate() ;
        Quaternion getConjugate() const;
        Vector3D toVector3D() const;
        Matrix4x4 toMatrix() const;

        static double dot(const Quaternion &lhs, const Quaternion &rhs);
        static Quaternion lerp(const Quaternion &a, const Quaternion &b, double t);
        static Quaternion slerp(const Quaternion &a, const Quaternion &b, double t);

        Quaternion operator*(double s);

        friend Quaternion operator + (const Quaternion& lhs, const Quaternion& rhs);
        friend Quaternion operator - (const Quaternion& lhs, const Quaternion& rhs);
        friend Quaternion operator * (const Quaternion& lhs, const Quaternion& rhs);
    
        //将向量v利用四元数执行旋转,此时该四元数应当==(cos(theta/2),xsin(theta/2),ysin(theta/2),zsin(theta/2))
        //且x^2+y^2+z^2=1 ，其中theta为旋转角度，(x,y,z)为旋转轴方向)
        Vector3D rotate(const Vector3D& v) const;
    };

}
#endif // QUATERNION_H
