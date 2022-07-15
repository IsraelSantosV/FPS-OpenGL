//
// Created by Israel on 09/04/2022.
//

#ifndef VOXENGINE_PRIMIVITES_H
#define VOXENGINE_PRIMIVITES_H

#include "vox-engine/component/Mesh.h"

class Primitives {
public:
    static DrawFunction* primitiveCube(){
        return [](Entity*){
            glBegin(GL_POLYGON);
            //glColor3f(   1.0,  1.0, 1.0 );
            glVertex3f(  1.0, -1.0, 1.0 );
            glVertex3f(  1.0,  1.0, 1.0 );
            glVertex3f( -1.0,  1.0, 1.0 );
            glVertex3f( -1.0, -1.0, 1.0 );
            glEnd();

            glBegin(GL_POLYGON);
            //glColor3f(  1.0,  0.0,  1.0 );
            glVertex3f( 1.0, -1.0, -1.0 );
            glVertex3f( 1.0,  1.0, -1.0 );
            glVertex3f( 1.0,  1.0,  1.0 );
            glVertex3f( 1.0, -1.0,  1.0 );
            glEnd();

            // Green side - LEFT
            glBegin(GL_POLYGON);
            //glColor3f(   0.0,  1.0,  0.0 );
            glVertex3f( -1.0, -1.0,  1.0 );
            glVertex3f( -1.0,  1.0,  1.0 );
            glVertex3f( -1.0,  1.0, -1.0 );
            glVertex3f( -1.0, -1.0, -1.0 );
            glEnd();

            // Blue side - TOP
            glBegin(GL_POLYGON);
            //glColor3f(   0.0,  0.0,  1.0 );
            glVertex3f(  1.0,  1.0,  1.0 );
            glVertex3f(  1.0,  1.0, -1.0 );
            glVertex3f( -1.0,  1.0, -1.0 );
            glVertex3f( -1.0,  1.0,  1.0 );
            glEnd();

            // Red side - BOTTOM
            glBegin(GL_POLYGON);
            //glColor3f(   1.0,  0.0,  0.0 );
            glVertex3f(  1.0, -1.0, -1.0 );
            glVertex3f(  1.0, -1.0,  1.0 );
            glVertex3f( -1.0, -1.0,  1.0 );
            glVertex3f( -1.0, -1.0, -1.0 );
            glEnd();
        };
    }

    static DrawFunction* primitiveSphere(){
        return [](Entity*){
            glutSolidSphere(1, 50, 50);
        };
    }

    static DrawFunction* primitiveCylinder(){
        return [](Entity*){
            glutSolidCylinder(1, 1, 50, 10);
        };
    }
};

#endif //VOXENGINE_PRIMIVITES_H
