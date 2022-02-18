//
// Created by Israel Santos Vieira on 18/02/2022.
//

#ifndef OPENGL_CUBEMESH_H
#define OPENGL_CUBEMESH_H

#include <GL/glut.h>
#include "../headers/Mesh.h"
#include "../headers/WorldObject.h"

class CubeMesh : public Mesh {
public:
    CubeMesh(bool wired) {
        m_Wired = wired;
    };
protected:
    bool m_Wired;
    void drawProperties(){
        WorldObject* wo = getObject();
        Vector3 position = wo->getPosition();
        Vector3 rotation = wo->getRotation();
        Vector3 scale = wo->getScale();

        glScalef(scale.X(), scale.Y(), scale.Z());
        glRotatef(0, rotation.X(), rotation.Y(), rotation.Z());
        glTranslatef(position.X(), position.Y(), position.Z());
        if(m_Wired){
            glutWireCube(DEFAULT_SIZE);
        }
        else{
            glutSolidCube(DEFAULT_SIZE);
        }
    };
};


#endif //OPENGL_CUBEMESH_H
