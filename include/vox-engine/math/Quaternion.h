//
// Created by Israel on 05/04/2022.
//

#ifndef VOXENGINE_QUATERNION_H
#define VOXENGINE_QUATERNION_H

#include "Matrix3.h"
#include "Vector3.h"

class Quaternion {
public:
    static const Quaternion ZERO;

    float s;
    Vector3 v;

    Quaternion();
    Quaternion(float uS,Vector3& uV);
    ~Quaternion();
    Quaternion(const Quaternion & value);

    inline Quaternion& operator=(const Quaternion& value);
    void operator+=(const Quaternion& q);
    Quaternion operator+(const Quaternion& q)const;
    void operator-=(const Quaternion& q);
    Quaternion operator-(const Quaternion& q)const;
    void operator*=(const Quaternion& q);
    Quaternion operator*(const Quaternion& q)const;
    Quaternion operator*(const Vector3& uValue)const;
    void operator*=(const float value);
    Quaternion operator*(const float value)const;
    bool operator!=(const Quaternion& q) const;

    Quaternion multiply(const Quaternion& q)const;
    float dot(Quaternion& q);
    float norm();
    void normalize();
    void convertToUnitNormQuaternion();
    Quaternion conjugate();
    Quaternion inverse();
    void inverse(Quaternion& q);
    Matrix3 transformQuaternionToMatrix3n();
    void transformEulerAnglesToQuaternion(float x,float y, float z);
    Vector3 transformQuaternionToEulerAngles();
    void transformMatrix3nToQuaternion(Matrix3 &uMatrix);
    Vector3 rotateVectorAboutAngleAndAxis(float uAngle, Vector3& target, Vector3& uAxis);
    void show();
};


#endif //VOXENGINE_QUATERNION_H
