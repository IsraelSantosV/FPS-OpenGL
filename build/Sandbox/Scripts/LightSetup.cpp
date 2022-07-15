//
// Created by Israel on 20/04/2022.
//

#include "vox-engine/core.h"

class LightSetup : public Behaviour {
public:
    void Update() override {
        if(InputManager::keyPressed(InputManager::KEY_1)){
            LightManager::enableLights();
        }
        else if(InputManager::keyPressed(InputManager::KEY_2)){
            LightManager::disableLights();
        }
    }
};