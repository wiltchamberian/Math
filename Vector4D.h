#ifndef VECTOR4D_H
#define VECTOR4D_H

#include "MathUtils.h"
#include "Vector3D.h"

/**
 * @projectName   SoftRenderer
 * @brief         4D vector class.
 * @author        YangWC
 * @date          2019-04-28
 */
namespace Sun
{
    class Vector4D
    {
    public:
        float x,y,z,w;

        // constructors
        Vector4D():x(0.0f), y(0.0f), z(0.0f), w(0.0f){}
        Vector4D(float newX, float newY, float newZ, float newW):x(newX), y(newY), z(newZ), w(newW){}
        Vector4D(const float * rhs):x(*rhs), y(*(rhs+1)), z(*(rhs+2)), w(*(rhs+3)){}
        Vector4D(const Vector4D &rhs):x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w){}
        Vector4D(const Vector3D & rhs):	x(rhs.x), y(rhs.y), z(rhs.z), w(1.0f){}
        ~Vector4D() = default;

        // setter,getter
        void set(float newX, float newY, float newZ, float newW){x=newX;y=newY;z=newZ;w=newW;}
        void setX(float newX) {x = newX;}
        void setY(float newY) {y = newY;}
        void setZ(float newZ) {z = newZ;}
        void setW(float newW) {w = newW;}
        double getX() const {return x;}
        double getY() const {return y;}
        double getZ() const {return z;}
        double getW() const {return w;}

        // product
        double dotProduct(const Vector4D &rhs) const {return x*rhs.x + y*rhs.y + z*rhs.z + w*rhs.w;}

        // linear interpolation
        Vector4D lerp(const Vector4D &v2, float factor) const {return (*this)*(1.0f-factor) + v2*factor;}
        Vector4D QuadraticInterpolate(const Vector4D &v2, const Vector4D &v3, float factor) const
        {return (*this)*(1.0f-factor)*(1.0f-factor)+v2*2.0f*factor*(1.0f-factor)+v3*factor*factor;}

        // overloaded operators
        Vector4D operator*(const float rhs) const {return Vector4D(x*rhs, y*rhs, z*rhs, w*rhs);}
        Vector4D operator/(const float rhs) const
        {return (equal(rhs,0.0f))?Vector4D(0.0f, 0.0f, 0.0f, 0.0f):Vector4D(x/rhs, y/rhs, z/rhs, w/rhs);}

        bool operator==(const Vector4D &rhs) const {return (equal(x,rhs.x)&&equal(y,rhs.y)&&equal(z,rhs.z)&&equal(w,rhs.w));}
        bool operator!=(const Vector4D &rhs) const {return !((*this)==rhs);}

        void operator+=(const Vector4D &rhs) {x+=rhs.x;y+=rhs.y;z+=rhs.z;w+=rhs.w;}
        void operator-=(const Vector4D & rhs) {x-=rhs.x;y-=rhs.y;z-=rhs.z;w-=rhs.w;}
        void operator*=(const float rhs){x*=rhs;y*=rhs;z*=rhs;w*=rhs;}
        void operator/=(const float rhs){if(!equal(rhs,0.0f)){x/=rhs; y/=rhs; z/=rhs; w/=rhs;}}

        Vector4D operator-() const {return Vector4D(-x, -y, -z, -w);}
        Vector4D operator+() const {return *this;}

        friend Vector4D operator+(const Vector4D& l, const Vector4D& r)
        {
            return Vector4D(l.x + r.x, l.y + r.y, l.z + r.z, l.w + r.w);
        }
        friend Vector4D operator-(const Vector4D& l, const Vector4D& r)
        {
            return Vector4D(l.x - r.x, l.y - r.y, l.z - r.z, l.w - r.w);
        }
    };

}

#endif // VECTOR4D_H
