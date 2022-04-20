//
// Created by Israel on 05/04/2022.
//

#include "vox-engine/core.h"
#include "../Scripts/Health.cpp"
#include "../Scripts/CubeAnimation.cpp"

class MainScene : public Scene {
public:
    void Load(){
        Entity* camera = instantiate("MainCamera");
        Camera* mainCamera = camera->addComponent<Camera>();
        mainCamera->setMode(FREE);
        mainCamera->setLookAt(vec3(0,0,0));
        mainCamera->setClipping(.1, 1000);
        mainCamera->setFOV(45);
        camera->transform->setPosition(vec3(0,0,-1));

        Camera::useDefaultCameraController = true;

        Entity* player = instantiate("Player");
        player->addComponent<Health>();

        Entity* cube = instantiate("Cube", Primitives::primitiveCube());
        cube->getComponent<Mesh>()->setColor(vec3(1,0,0));
        cube->transform->setPosition(vec3(0,0, 3));
        cube->addComponent<CubeAnimation>();

        Entity* insideCube = instantiate("InsideCylinder", Primitives::primitiveCylinder());

        //insideCube->mesh->setColor(vec3(1,1,1));
        insideCube->transform->setScale(vec3(0.8,2,1));
        insideCube->transform->setPosition(vec3(-2,0,0));
        insideCube->transform->setParent(cube->transform);

        Entity* mostInsideCube = instantiate("MostInsideSphere", Primitives::primitiveSphere());
        mostInsideCube->transform->setPosition(vec3(1, 1.5, 1));
        //mostInsideCube->getComponent<Mesh>()->setColor(vec3(1, 1, 0));
        //mostInsideCube->transform->setParent(insideCube->transform);
        //mostInsideCube->setEnable(false);

        //Ground texture
        const int groundScale = 50;
        const int groundHeight = 5;

        Entity* ground = instantiate("Ground");
        Mesh* groundMesh = new Mesh();
        groundMesh->setDrawFunction([](Entity* entity){
            glEnable(GL_TEXTURE_2D);
            glColor4f(1,1,1,1);
            GLuint texture;
            glGenTextures(1,&texture);

//            unsigned char texture_data[2][2][4] =
//                    {
//                            0,0,0,255,  255,255,255,255,
//                            255,255,255,255,    0,0,0,255
//                    };

            void* texture_data = Tools::loadTexture("resources/textures/Grass_7.png");

            glBindTexture(GL_TEXTURE_2D,texture);
            glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,2,2,0,GL_RGBA,GL_UNSIGNED_BYTE,texture_data);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);

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