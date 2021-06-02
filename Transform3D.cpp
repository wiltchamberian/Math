#include "Transform3D.h"
#include "MathUtils.h"
#include "Quaternion.h"

namespace Sun
{

    Transform3D::Transform3D()
        :scale_(1.0,1.0,1.0)
    {
    }

    Transform3D::Transform3D(const Vector3D& translation, const Quaternion& quater,
        const Vector3D& scale) {
        translation_ = translation;
        rotation_ = quater;
        scale_ = scale;
    }

    Transform3D::~Transform3D()
    {

    }

    void Transform3D::translate(const Vector3D& world_space_v) {
        translation_ += world_space_v;
    }

    void Transform3D::scale(const Vector3D& scale) {
        scale_.x *= scale.x;
        scale_.y *= scale.y;
        scale_.z *= scale.z;
    }

    void Transform3D::scale(float x, float y, float z)
    {
        scale_.x *= x;
        scale_.y *= y;
        scale_.z *= z;
    }

    void Transform3D::rotate(const Vector3D& axis, double radians)
    {
        Quaternion q;
        q.setRotateAxisAndRadius(axis, radians);
        rotation_ = q * rotation_;
    }

    Matrix4x4 Transform3D::toMatrix() const
    {
        Matrix4x4 res;
        Matrix4x4 rotation = rotation_.toMatrix();
        Matrix4x4 trans, scals;
        scals = Matrix4x4::getScale(scale_);
        trans = Matrix4x4::getTranslation(translation_);
        //res = trans * scals * rotation; //FIXME make sure
        res = trans * rotation * scals;
        return res;

    }

    Vector3D Transform3D::z_direction() const
    {
        return rotation_.rotate(Vector3D(0, 0, 1));
    }

    Vector3D Transform3D::x_direction() const
    {
        return rotation_.rotate(Vector3D(1, 0, 0));
    }

    Vector3D Transform3D::y_direction() const
    {
        return rotation_.rotate(Vector3D(0, 1, 0));
    }

    void Transform3D::setScale(const Vector3D& s) {
        scale_ = s;
    }

    void Transform3D::setRotation(const Quaternion& r) {
        rotation_ = r;
    }

    void Transform3D::setRotation(float a, float b, float c, float d) {
        rotation_ = Quaternion(a, b, c, d);
    }

    void Transform3D::setTranslation(const Vector3D& t) {
        translation_ = t;
    }

    void Transform3D::setMatrix(const Matrix4x4& matrix)
    {
        //model = matrix;
        matrix.decomposeTransRotScale(translation_, rotation_, scale_);
    }

    //TODO
    Transform3D Transform3D::getInverse()
    {
        return Transform3D();
    }


}