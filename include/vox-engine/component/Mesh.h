//
// Created by Israel on 05/04/2022.
//

#ifndef VOXENGINE_MESH_H
#define VOXENGINE_MESH_H

#include "vox-engine/component/Component.h"
#include "vox-engine/math/Quaternion.h"
#include "vox-engine/resources/OpenGL.h"
typedef void DrawFunction(Entity*);

class Mesh : public Component {
public:
    void setDrawFunction(DrawFunction function){
        m_DrawFunction = function;
    }

    void draw(Vector3 position, Quaternion rotation, Vector3 scale){
        glPushMatrix();
            glColor4f(m_Color.x, m_Color.y, m_Color.z, m_Alpha);
            glScalef(scale.x, scale.y, scale.z);
            glRotatef(0, rotation.v.x, rotation.v.y, rotation.v.z);
            glTranslatef(position.x, position.y, position.z);

            if(m_DrawFunction != nullptr) {
                m_DrawFunction(getEntity());
            }

        glPopMatrix();
    }

    void setColor(Vector3 color, float alpha = 1){
        m_Color = color;
        m_Alpha = alpha;
    }
protected:
    Vector3 m_Color = Vector3::ONE;
    float m_Alpha = 1;
private:
    DrawFunction* m_DrawFunction;
};


#endif //VOXENGINE_MESH_H
