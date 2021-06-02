#ifndef __TRANSFORM_H
#define __TRANSFORM_H

#include "Vector3D.h"
#include "Matrix4x4.h"
#include "Quaternion.h"

namespace Sun
{
    //描述物体的空间信息，物体上任意点的坐标是相对于局部坐标系，
    //经过Transform3D可以转为世界坐标
    class Transform3D
    {
    public:
        Transform3D();
        Transform3D(const Vector3D& translation, const Quaternion& quater,
            const Vector3D& scale);
        ~Transform3D();
        void translate(const Vector3D& world_space_v);
        void scale(const Vector3D& scale);
        void scale(float x, float y, float z);
        //this rotate is relative the local coordinate
        void rotate(const Vector3D& axis, double radians);
        //相对于父亲坐标系的某个轴旋转
        //void rotateRelatvieParent(const Vector3D& axis, double radians);
        Matrix4x4 toMatrix() const;

        Vector3D z_direction() const;
        Vector3D x_direction() const;
        Vector3D y_direction() const;

        void setScale(const Vector3D& s);
        void setRotation(const Quaternion& r);
        void setRotation(float a, float b, float c, float d);
        void setTranslation(const Vector3D& t);
        void setMatrix(const Matrix4x4& matrix);

        // Transformation getter.
        Vector3D getTranslation() const { return translation_; }
        Quaternion getRotation() const { return rotation_; }
        Vector3D getScale() const { return scale_; }

        inline friend Transform3D operator * (const Transform3D& t2, const Transform3D& t1);

        Transform3D getInverse();
        //之所以开放为公有原因有以下几点，1，可以支持set,get访问实际已经相当于
        //共有，2，用户直接修改不会破会对象的内部状态；
    public:
        //平移
        Vector3D translation_;
        //旋转
        Quaternion rotation_;
        //放缩
        Vector3D scale_;

        //Matrix4x4 _model;
    };

    //由于通常变换作用于矢量采用左乘法，所以(t2*t1)(p) = t2(t1(p))
    //每个变换都想相对于局部坐标系而言的连轴变换
    inline Transform3D operator* (const Transform3D& t2, const Transform3D& t1) {
        Transform3D result;

        result.rotation_ = t2.rotation_ * t1.rotation_;
        result.translation_ = t2.translation_ + t2.rotation_.rotate(t2.scale_ * t1.translation_);
        result.scale_ = t2.scale_ * t1.scale_;

        return result;
    }
}



#endif

