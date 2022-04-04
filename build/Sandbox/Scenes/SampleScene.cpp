//
// Created by zetta on 01/04/2022.
//

#ifndef DEMO_SCENE_CPP
#define DEMO_SCENE_CPP

#include "../../VoxEngineCore.h"
#include "../Scripts/CameraController.cpp"
#include "../Scripts/StateController.cpp"
#include "../Scripts/Spawner.cpp"


class SampleScene : public Scene {
public:
    void Load(){
        //Camera settings
        Entity* camera = instantiate("Camera");
        camera->addComponent<Camera>();
        camera->getComponent<Transform>()->setPosition(Vector3f(0, 1, -6));
        camera->getComponent<Transform>()->setRotation(Vector3f(0,0,0));

        camera->addComponent<CameraController>();
        camera->addComponent<StateController>();
        camera->addComponent<Spawner>();

        //Entities settings
        Entity* floor = instantiate("Floor");
        CustomMesh* mesh = floor->addComponent<CustomMesh>();
        mesh->setMesh([](){ glutSolidCube(1); });

        floor->getComponent<Transform>()->setScale(Vector3f(10, 10, 10));
    }

    void OnUnload(){ }
};

#endif // DEMO_SCENE_CPP