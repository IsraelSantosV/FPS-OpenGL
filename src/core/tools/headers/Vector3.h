//
// Created by Israel Santos Vieira on 17/02/2022.
//

#ifndef OPENGL_VECTOR3_H
#define OPENGL_VECTOR3_H

class Vector3 {
private:
    float m_X;
    float m_Y;
    float m_Z;
public:
    Vector3();
    Vector3(float x, float y, float z);
    Vector3(float x, float y);
    void set(float x, float y, float z);
    float X();
    float Y();
    float Z();
};

#endif //OPENGL_VECTOR3_H
