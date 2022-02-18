//
// Created by Israel Santos Vieira on 18/02/2022.
//

#include "headers/Mesh.h"
#include <GL/glut.h>

Mesh::Mesh(WorldObject *wo) {
    wo->registerComponent(this);
}

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
