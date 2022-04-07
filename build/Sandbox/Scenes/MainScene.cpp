//
// Created by Israel on 05/04/2022.
//

#include "vox-engine/core.h"
#include "../Scripts/Health.cpp"

class MainScene : public Scene {
public:
    void Load(){
        Entity* player = instantiate("Player");
        player->addComponent<Health>();

        const int groundScale = 50;
        const int groundHeight = 5;

        Entity* ground = instantiate("Ground");
        Mesh* groundMesh = new Mesh();
        groundMesh->setDrawFunction([](Entity* entity){
            glEnable(GL_TEXTURE_2D);
            glColor4f(1,1,1,1);
            GLuint texture;
            glGenTextures(1,&texture);

            unsigned char texture_data[2][2][4] =
                    {
                            0,0,0,255,  255,255,255,255,
                            255,255,255,255,    0,0,0,255
                    };

            glBindTexture(GL_TEXTURE_2D,texture);
            glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,2,2,0,GL_RGBA,GL_UNSIGNED_BYTE,texture_data);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);

            glBegin(GL_QUADS);
            glTexCoord2f(0.0,0.0);  glVertex3f(-groundScale,-groundHeight,-groundScale);
            glTexCoord2f(groundScale/2,0.0);  glVertex3f(groundScale,-groundHeight,-groundScale);
            glTexCoord2f(groundScale/2,groundScale/2);  glVertex3f(groundScale,-groundHeight,groundScale);
            glTexCoord2f(0.0,groundScale/2);  glVertex3f(-groundScale,-groundHeight,groundScale);
            glEnd();
            glDisable(GL_TEXTURE_2D);
        });

        ground->setMesh(groundMesh);
    }
};