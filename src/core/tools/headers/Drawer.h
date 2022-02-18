//
// Created by Israel Santos Vieira on 18/02/2022.
//

#ifndef OPENGL_DRAWER_H
#define OPENGL_DRAWER_H


#include "Vector3.h"

class Drawer {
private:
    static void draw_cube(bool wired);
    static void draw_sphere(bool wired, float radius, int slices, int stacks);
public:
    static void drawSolidCube(Vector3 worldPosition, Vector3 size, Vector3 color = Vector3(1,1,1), float alpha = 1);
    static void drawWiredCube(Vector3 worldPosition, Vector3 size, Vector3 color = Vector3(1,1,1), float alpha = 1);
    static void drawSolidSphere(Vector3 worldPosition, float radius, int slices, int stacks,
                                Vector3 color = Vector3(1,1,1), float alpha = 1);
    static void drawWiredSphere(Vector3 worldPosition, float radius, int slices, int stacks,
                                Vector3 color = Vector3(1,1,1), float alpha = 1);
};


#endif //OPENGL_DRAWER_H
