//
// Created by Israel on 05/04/2022.
//

#ifndef VOXENGINE_MESH_H
#define VOXENGINE_MESH_H

#include "vox-engine/component/Component.h"
#include "vox-engine/resources/OpenGL.h"
#include "vox-engine/resources/Math.h"

typedef void DrawFunction(Entity*);

class Mesh : public Component {
public:
    void setDrawFunction(DrawFunction function){
        m_DrawFunction = function;
    }

    void draw(vec3 position, quat rotation, vec3 scale){
        glPushMatrix();
            glColor4f(m_Color.x, m_Color.y, m_Color.z, m_Alpha);
            glScalef(scale.x, scale.y, scale.z);
            glRotatef(0, rotation.x, rotation.y, rotation.z);
            glTranslatef(position.x, position.y, position.z);

            if(m_DrawFunction != nullptr) {
                m_DrawFunction(getEntity());
            }

        glPopMatrix();
    }

    void setColor(vec3 color, float alpha = 1){
        m_Color = color;
        m_Alpha = alpha;
    }
protected:
    vec3 m_Color = vec3(1,1,1);
    float m_Alpha = 1;
private:
    DrawFunction* m_DrawFunction;
};


#endif //VOXENGINE_MESH_H
