//
// Created by Israel on 05/04/2022.
//

#ifndef VOXENGINE_MESH_H
#define VOXENGINE_MESH_H

#include "vox-engine/component/Component.h"
#include "vox-engine/resources/OpenGL.h"
#include "vox-engine/resources/Math.h"
#include "vox-engine/resources/Texture.h"

typedef void DrawFunction(Entity*);

class Mesh : public Component {
public:
    void setDrawFunction(DrawFunction function){
        m_DrawFunction = function;
    }

    void drawTexture(){
        if(m_Texture != nullptr){
            m_Texture->bind();
        }
    }

    void draw(){
        glPushMatrix();
            glColor4f(m_Color.x, m_Color.y, m_Color.z, m_Alpha);

            if(m_DrawFunction != nullptr) {
                m_DrawFunction(getEntity());
            }

        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    }

    void setColor(vec3 color, float alpha = 1){
        m_Color = color;
        m_Alpha = alpha;
    }

    void setTexture(Texture* texture){
        m_Texture = texture;
    }
protected:
    vec3 m_Color = vec3(1,1,1);
    float m_Alpha = 1;
private:
    DrawFunction* m_DrawFunction;
    Texture* m_Texture;
};


#endif //VOXENGINE_MESH_H
