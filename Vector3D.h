/**
 * @projectName   SoftRenderer
 * @brief         3D vector class.
 * @author        YangWC , revised by ACE
 * @date          2019-04-28
 */

#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "MathUtils.h"

namespace Sun
{
    class Vector3D
    {
    public:
        float x,y,z;

        // constructors
        Vector3D():x(0.0f), y(0.0f), z(0.0f){}
        Vector3D(float newX, float newY, float newZ):x(newX), y(newY), z(newZ){}
        Vector3D(const float * rhs):x(*rhs), y(*(rhs+1)), z(*(rhs+2)){}
        Vector3D(const Vector3D &rhs):x(rhs.x), y(rhs.y), z(rhs.z){}
        ~Vector3D() = default;

        void clear() { x = 0.f; y = 0.f; z = 0.f; }
        // setter,getter
        void set(float newX, float newY, float newZ){x=newX;y=newY;z=newZ;}
        void setX(float newX) {x = newX;}
        void setY(float newY) {y = newY;}
        void setZ(float newZ) {z = newZ;}
        float getX() const {return x;}
        float getY() const {return y;}
        float getZ() const {return z;}

        bool isZero() const { return equal(x, 0) && equal(y, 0) && equal(z, 0); }
        // normalization
        void normalize();
        Vector3D getNormalized() const;
        Vector3D sign() const;

        // length caculation
        float getLength() const {return static_cast<float>(sqrt(x*x+y*y+z*z));}
        float getSquaredLength() const {return x*x+y*y+z*z;}

        // product
        float dotProduct(const Vector3D &rhs) const {return x*rhs.x + y*rhs.y + z*rhs.z;}
        Vector3D crossProduct(const Vector3D &rhs) const
        {return Vector3D(y*rhs.z - z*rhs.y, z*rhs.x - x*rhs.z, x*rhs.y - y*rhs.x);}

        // linear interpolation
        Vector3D lerp(const Vector3D &v2, float factor) const {return (*this)*(1.0f-factor) + v2*factor;}
        Vector3D QuadraticInterpolate(const Vector3D &v2, const Vector3D &v3, float factor) const
        {return (*this)*(1.0f-factor)*(1.0f-factor) + v2*2.0f*factor*(1.0f-factor) + v3*factor*factor;}

        // overloaded operators
        Vector3D operator+(const Vector3D &rhs) const {return Vector3D(x + rhs.x, y + rhs.y, z + rhs.z);}
        Vector3D operator-(const Vector3D &rhs) const {return Vector3D(x - rhs.x, y - rhs.y, z - rhs.z);}
        Vector3D operator*(const float rhs) const {return Vector3D(x*rhs, y*rhs, z*rhs);}
        Vector3D operator/(const float rhs) const {return (equal(rhs,0.0f))?Vector3D(0.0f, 0.0f, 0.0f):Vector3D(x/rhs, y/rhs, z/rhs);}

        bool operator==(const Vector3D &rhs) const {return (equal(x,rhs.x) && equal(y,rhs.y) && equal(z,rhs.z));}
        bool operator!=(const Vector3D &rhs) const {return !((*this)==rhs);}

        void operator+=(const Vector3D &rhs) {x+=rhs.x;y+=rhs.y;z+=rhs.z;}
        void operator-=(const Vector3D & rhs) {x-=rhs.x;y-=rhs.y;z-=rhs.z;}
        void operator*=(const float rhs){x*=rhs;y*=rhs;z*=rhs;}
        void operator/=(const float rhs){if(!equal(rhs,0.0f)){x/=rhs; y/=rhs; z/=rhs;}}

        Vector3D operator-() const {return Vector3D(-x, -y, -z);}
        Vector3D operator+() const {return *this;}

        friend bool operator<(const Vector3D& v1, const Vector3D& v2) {
            return v1.x < v2.x 
                || (v1.x==v2.x)&&(v1.y < v2.y) 
                || (v1.x==v2.x)&&(v1.y==v2.y)&&(v1.z<v2.z);
        }

        float& operator[](int i) {
            return ((float*)this)[i];
        }

        inline friend Vector3D operator* (const Vector3D& v1, const Vector3D& v2);
    };

    //判断两个vector是否平行，0向量与所有向量平行
    inline bool parallel(const Vector3D& v1, const Vector3D& v2) {
        return equal(v1.x * v2.y, v2.x * v1.y) && equal(v1.x * v2.z, v1.z * v2.x);
    }

    inline Vector3D operator* (const Vector3D& v1, const Vector3D& v2) {
        return Vector3D(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
    }

}

#endif // VECTOR3D_H
