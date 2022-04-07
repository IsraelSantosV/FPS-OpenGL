//
// Created by Israel on 05/04/2022.
//

#ifndef VOXENGINE_MATRIX3_H
#define VOXENGINE_MATRIX3_H

#include "Vector3.h"

class Matrix3 {
public:
    float matrixData[9]={0.0};

    Matrix3();
    Matrix3(float m0,float m3,float m6,float m1,float m4,float m7,float m2,float m5,float m8);
    ~Matrix3();

    Matrix3& operator=(const Matrix3& value);
    Matrix3 operator+(const Matrix3 &m) const;
    void operator+=(const Matrix3 &m);
    Matrix3 operator*(const float s) const;
    void operator*=(const float s);
    Vector3 operator*(const Vector3 & v) const;
    Vector3 transformVectorByMatrix(const Vector3& v) const;
    Matrix3 operator*(const Matrix3& m) const;
    void operator*=(const Matrix3& m);

    void setMatrixAsIdentityMatrix();
    void setMatrixAsInverseOfGivenMatrix(const Matrix3& m);
    Matrix3 getInverseOfMatrix() const;
    void invertMatrix();
    float getMatrixDeterminant() const;
    void setMatrixAsTransposeOfGivenMatrix(const Matrix3& m);
    Matrix3 getTransposeOfMatrix() const;
    void invertAndTransposeMatrix();
    void makeRotationMatrixAboutXAxisByAngle(float uAngle);
    void makeRotationMatrixAboutYAxisByAngle(float uAngle);
    void makeRotationMatrixAboutZAxisByAngle(float uAngle);
    void transformMatrixAboutXAxisByAngle(float uAngle);
    void transformMatrixAboutYAxisByAngle(float uAngle);
    void transformMatrixAboutZAxisByAngle(float uAngle);
    void show();
};


#endif //VOXENGINE_MATRIX3_H
