//
// Created by zetta on 01/04/2022.
//

#ifndef STATE_CONTROLLER_SCRIPT_CPP
#define STATE_CONTROLLER_SCRIPT_CPP

#include "../../VoxEngineCore.h"

class StateController : public Behaviour {
public:
    bool toggleCursorMode = false;
    bool toggleVsyncMode = true;

    void Start() {
        toggleCursor();
    }

    void Update(){
        if (InputManager::keyPressed(InputManager::KEY_C))
            toggleCursor();

        if (InputManager::keyPressed(InputManager::KEY_V))
            toggleVSync();

        if (InputManager::keyPressed(InputManager::KEY_B))
            toggleDebug();

        if (InputManager::keyPressed(InputManager::KEY_ESCAPE))
            Application::stop();

        if (InputManager::keyPressed(InputManager::KEY_ENTER)) {
            Transform* transform = getEntity()->transform;
            std::string sp = "pos: " + std::to_string(transform->getPositionWorld().x()) +
                             ", " + std::to_string(transform->getPositionWorld().y()) +
                             ", " + std::to_string(transform->getPositionWorld().z());

            std::string sr = "rot: " + std::to_string(transform->getRotation().getX()) +
                             ", " + std::to_string(transform->getRotation().getY()) +
                             ", " + std::to_string(transform->getRotation().getZ()) +
                             ", " + std::to_string(transform->getRotation().getW());


            Logger::logln(sp);
            Logger::logln(sr);
            Logger::br();
        }

        if(InputManager::keyPressed(InputManager::KEY_G)){
            FrameBuffer::clearDefaultBuffer();
        }
    }

    void toggleCursor() {
        if (toggleCursorMode) {
            InputManager::setCursorMode(InputManager::CursorMode::DISABLED);
        } else {
            InputManager::setCursorMode(InputManager::CursorMode::NORMAL);
        }
        toggleCursorMode = !toggleCursorMode;
    }

    void toggleVSync() {
        Display::setVSync(toggleVsyncMode);
        toggleVsyncMode = !toggleVsyncMode;
    }

    void toggleDebug() {
        Renderer::setDebug((Renderer::getDebugMode() + 1) % Renderer::MAX_DEBUG);
    }
};

#endif // STATE_CONTROLLER_SCRIPT_CPP