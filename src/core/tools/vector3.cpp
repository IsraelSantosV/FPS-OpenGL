//
// Created by Israel Santos Vieira on 17/02/2022.
//

#include "headers/vector3.h"

vector3::vector3() {
    m_X = new float(0);
    m_Y = new float(0);
    m_Z = new float(0);
}

vector3::vector3(float x, float y, float z) {
    m_X = new float(x);
    m_Y = new float(y);
    m_Z = new float(z);
}

vector3::vector3(float x, float y) {
    m_X = new float(x);
    m_Y = new float(y);
    m_Z = new float(0);
}

vector3::~vector3() {
    delete m_X;
    delete m_Y;
    delete m_Z;
}

void vector3::set(float x, float y, float z) {
    m_X = new float(x);
    m_Y = new float(y);
    m_Z = new float(z);
}

float vector3::X() {
    return *m_X;
}

float vector3::Y() {
    return *m_Y;
}

float vector3::Z() {
    return *m_Z;
}
