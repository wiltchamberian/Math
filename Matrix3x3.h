#ifndef __MATRIX3X3_H
#define __MATRIX3X3_H

#include "MathUtils.h"
#include "Vector4D.h"

/**
 * @projectName   SoftRenderer
 * @brief         4x4 matrix class.
 * @author        YangWC
 * @date          2019-04-28
 */
namespace Sun
{

    class Matrix3x3
    {
    public:
        float entries[9];

        // constructors
        Matrix3x3() { loadIdentity(); }
        Matrix3x3(float e0, float e1, float e2, float e3,
            float e4, float e5, float e6, float e7,
            float e8);
        Matrix3x3(const float* rhs);
        Matrix3x3(const Matrix3x3& rhs);
        ~Matrix3x3() = default;

        // setter,getter
        void setEntry(int position, float value);
        float getEntry(int position) const;
        Vector3D getRow(int position) const;
        Vector3D getColumn(int position) const;
        void loadIdentity();
        void loadZero();

        // overloaded operators
        Matrix3x3 operator+(const Matrix3x3& rhs) const;
        Matrix3x3 operator-(const Matrix3x3& rhs) const;
        Matrix3x3 operator*(const Matrix3x3& rhs) const;
        Matrix3x3 operator*(const float rhs) const;
        Matrix3x3 operator/(const float rhs) const;

        bool operator==(const Matrix3x3& rhs) const;
        bool operator!=(const Matrix3x3& rhs) const;

        void operator+=(const Matrix3x3& rhs);
        void operator-=(const Matrix3x3& rhs);
        void operator*=(const Matrix3x3& rhs);
        void operator*=(const float rhs);
        void operator/=(const float rhs);

        Matrix3x3 operator-() const;
        Matrix3x3 operator+() const { return (*this); }
        Vector3D operator*(const Vector3D rhs) const;

        // inverse, transpose
        void inverted();
        Matrix3x3 getInverse() const;
        void transpose();
        Matrix3x3 getTranspose() const;
        void invertTranspose();
        Matrix3x3 getInverseTranspose() const;
        float determinant() const;

        // operation on space
        static Matrix3x3 getScale(const Vector3D& scaleFactor);
        static Matrix3x3 getRotationAxis(const double radians, const Vector3D& axis);
        static Matrix3x3 getRotationX(const double radians);
        static Matrix3x3 getRotationY(const double radians);
        static Matrix3x3 getRotationZ(const double radians);
    };

}


#endif