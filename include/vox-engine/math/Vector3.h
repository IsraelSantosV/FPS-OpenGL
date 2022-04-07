//
// Created by Israel on 05/04/2022.
//

#ifndef VOXENGINE_VECTOR3_H
#define VOXENGINE_VECTOR3_H

#include <cmath>
#include <iostream>
#include "Constants.h"

class Vector3 {
public:
    static const Vector3 ZERO;
    static const Vector3 ONE;

    static const Vector3 UNIT_X;
    static const Vector3 UNIT_Y;
    static const Vector3 UNIT_Z;

    static const Vector3 UP;
    static const Vector3 DOWN;
    static const Vector3 LEFT;
    static const Vector3 RIGHT;
    static const Vector3 FORWARD;
    static const Vector3 BACK;

    float x;
    float y;
    float z;

    Vector3();
    Vector3(float uX,float uY,float uZ);
    ~Vector3();
    Vector3(const Vector3& v);

    Vector3& operator=(const Vector3& v);
    void operator+=(const Vector3& v); //add vectors
    Vector3 operator+(const Vector3& v)const; //add vectors
    void operator-=(const Vector3& v); //subtract vectors
    Vector3 operator-(const Vector3& v)const; //subtract vectors
    void operator*=(const float s);
    Vector3 operator*(const float s)const;
    void operator /=(const float s);
    Vector3 operator/(const float s)const;
    float operator*(const Vector3& v) const;
    bool operator !=(const Vector3& v) const;

    float dot(const Vector3& v) const;
    float angle(const Vector3& v);
    void operator %=(const Vector3& v);
    Vector3 operator %(const Vector3& v) const;
    Vector3 cross(const Vector3& v) const;
    void conjugate();
    void normalize();
    float magnitude();
    float magnitudeSquare();
    void zero();
    void absolute();
    Vector3 rotateVectorAboutAngleAndAxis(float uAngle, Vector3& uAxis);

    void show();
    //Negate all components
    void negate();
};


#endif //VOXENGINE_VECTOR3_H
