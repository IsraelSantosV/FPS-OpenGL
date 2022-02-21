//
// Created by Israel Santos Vieira (Computer scientist) - All rights reserved
//

#ifndef FP_OPENGL_MESH_H
#define FP_OPENGL_MESH_H


#include "../tools/Vector3.h"

class Mesh {
private:
    Vector3 m_Color = Vector3(1,1,1);
    float m_Alpha = 1;
    void internal_drawing();
protected:
    void drawProperties();
public:
    void draw();
    void setColor(Vector3 color, float alpha = 1);
};


#endif //FP_OPENGL_MESH_H
