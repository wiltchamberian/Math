#ifndef __TRANSFORM_H
#define __TRANSFORM_H

#include "Vector3D.h"
#include "Matrix4x4.h"
#include "Quaternion.h"

namespace Sun
{
    //��������Ŀռ���Ϣ������������������������ھֲ�����ϵ��
    //����Transform3D����תΪ��������
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
        //����ڸ�������ϵ��ĳ������ת
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
        //֮���Կ���Ϊ����ԭ�������¼��㣬1������֧��set,get����ʵ���Ѿ��൱��
        //���У�2���û�ֱ���޸Ĳ����ƻ������ڲ�״̬��
    public:
        //ƽ��
        Vector3D translation_;
        //��ת
        Quaternion rotation_;
        //����
        Vector3D scale_;

        //Matrix4x4 _model;
    };

    //����ͨ���任������ʸ��������˷�������(t2*t1)(p) = t2(t1(p))
    //ÿ���任��������ھֲ�����ϵ���Ե�����任
    inline Transform3D operator* (const Transform3D& t2, const Transform3D& t1) {
        Transform3D result;

        result.rotation_ = t2.rotation_ * t1.rotation_;
        result.translation_ = t2.translation_ + t2.rotation_.rotate(t2.scale_ * t1.translation_);
        result.scale_ = t2.scale_ * t1.scale_;

        return result;
    }
}



#endif

