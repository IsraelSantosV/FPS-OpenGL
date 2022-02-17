//
// Created by Israel Santos Vieira on 17/02/2022.
//

#include "headers/Vector3.h"

Vector3::Vector3() {
    set(0,0,0);
}

Vector3::Vector3(float x, float y, float z) {
    set(x,y,z);
}

Vector3::Vector3(float x, float y) {
    set(x, y, 0);
}

void Vector3::set(float x, float y, float z) {
    m_X = x;
    m_Y = y;
    m_Z = z;
}

float Vector3::X() {
    return m_X;
}

float Vector3::Y() {
    return m_Y;
}

float Vector3::Z() {
    return m_Z;
}
