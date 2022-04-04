//
// Created by zetta on 01/04/2022.
//

#ifndef SPAWNER_CPP
#define SPAWNER_CPP

#include <GL/glut.h>
#include "../../VoxEngineCore.h"

class Spawner : public Behaviour {
public:
    void Update(){
        if (InputManager::keyPressed(InputManager::KEY_R)) {
            createEntity();
        }
    }

    void createEntity() {
        Entity *e = SceneManager::getCurrentScene()->instantiate("NewObject");
        e->getComponent<Transform>()->setPosition(
                Vector3f((float) (rand() % 10), (float) (rand() % 10), (float) (rand() % 10)));

        CustomMesh* targetMesh = e->addComponent<CustomMesh>();
        targetMesh->setMesh([](){ glutSolidCube(1); });
    }
};

#endif // SPAWNER_SCRIPT_CPP