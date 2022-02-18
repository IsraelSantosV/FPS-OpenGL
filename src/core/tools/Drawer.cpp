//
// Created by Israel Santos Vieira on 18/02/2022.
//

#include "headers/Drawer.h"
#include <GL/glut.h>
#define DEFAULT_SCALE 1

void Drawer::drawSolidCube(Vector3 worldPosition, Vector3 size, Vector3 color, float alpha) {
    glPushMatrix();
        glTranslatef(worldPosition.X(), worldPosition.Y(), worldPosition.Z());
        glScalef(size.X(), size.Y(), size.Z());
        glColor4f(color.X(), color.Y(), color.Z(), alpha);
        draw_cube(false);
    glPopMatrix();
}

void Drawer::drawWiredCube(Vector3 worldPosition, Vector3 size, Vector3 color, float alpha) {
    glPushMatrix();
        glTranslatef(worldPosition.X(), worldPosition.Y(), worldPosition.Z());
        glScalef(size.X(), size.Y(), size.Z());
        glColor4f(color.X(), color.Y(), color.Z(), alpha);
        draw_cube(true);
    glPopMatrix();
}

void Drawer::drawSolidSphere(Vector3 worldPosition, float radius, int slices, int stacks, Vector3 color, float alpha) {
    glPushMatrix();
        glTranslatef(worldPosition.X(), worldPosition.Y(), worldPosition.Z());
        glColor4f(color.X(), color.Y(), color.Z(), alpha);
        draw_sphere(false, radius, slices, stacks);
    glPopMatrix();
}

void Drawer::drawWiredSphere(Vector3 worldPosition, float radius, int slices, int stacks, Vector3 color, float alpha) {
    glPushMatrix();
        glTranslatef(worldPosition.X(), worldPosition.Y(), worldPosition.Z());
        glColor4f(color.X(), color.Y(), color.Z(), alpha);
        draw_sphere(true, radius, slices, stacks);
    glPopMatrix();
}

void Drawer::draw_cube(bool wired) {
    if(wired){
        glutWireCube(DEFAULT_SCALE);
    }
    else{
        glutSolidCube(DEFAULT_SCALE);
    }
}

void Drawer::draw_sphere(bool wired, float radius, int slices, int stacks) {
    if(wired){
        glutWireSphere(radius, slices, stacks);
    }
    else{
        glutSolidSphere(radius, slices, stacks);
    }
}