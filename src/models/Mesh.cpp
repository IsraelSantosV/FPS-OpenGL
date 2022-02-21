//
// Created by Israel Santos Vieira (Computer scientist) - All rights reserved
//

#include "Mesh.h"
#include <GL/glut.h>

void Mesh::draw() { internal_drawing(); }

void Mesh::internal_drawing() {
    glPushMatrix();
        glColor4f(m_Color.X(), m_Color.Y(), m_Color.Z(), m_Alpha);
        drawProperties();
    glPopMatrix();
}

void Mesh::drawProperties() { }

void Mesh::setColor(Vector3 color, float alpha) {
    m_Color.set(color.X(), color.Y(), color.Z());
    m_Alpha = alpha;
}