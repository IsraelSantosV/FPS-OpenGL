//
// Created by Israel Santos Vieira on 18/02/2022.
//

#ifndef OPENGL_MESH_H
#define OPENGL_MESH_H

#include "../../tools/headers/Vector3.h"
#include "WorldObject.h"
#define DEFAULT_SIZE 1

class Mesh : public Component {
private:
    Vector3 m_Color = Vector3(1,1,1);
    float m_Alpha = 1;
    void internal_drawing();
protected:
    void drawProperties();
public:
    Mesh(WorldObject* wo);
    void draw();
    void setColor(Vector3 color, float alpha = 1);
};


#endif //OPENGL_MESH_H
