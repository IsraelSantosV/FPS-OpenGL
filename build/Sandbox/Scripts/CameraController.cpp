//
// Created by zetta on 01/04/2022.
//

#include "../../VoxEngineCore.h"

class CameraController : public Behaviour {
public:
    float speed = 1;
    float mouseSensitivity = 0.6f;

    void Update() {
        Vector3f direction = Vector3f::ZERO;
        float shift = 1;
        if (InputManager::keyDown(InputManager::KEY_W)) direction.z() = 1;
        if (InputManager::keyDown(InputManager::KEY_S)) direction.z() = -1;
        if (InputManager::keyDown(InputManager::KEY_D)) direction.x() = -1;
        if (InputManager::keyDown(InputManager::KEY_A)) direction.x() = 1;
        if (InputManager::keyDown(InputManager::KEY_SPACE)) direction.y() = 1;
        if (InputManager::keyDown(InputManager::KEY_LEFT_CONTROL)) direction.y() = -1;

        if (InputManager::keyDown(InputManager::KEY_LEFT_SHIFT)) shift = 2.5f;

        Transform* transform = getEntity()->transform;
        transform->setPosition(transform->getPosition() +
                               (transform->forward() * direction.z() +
                                transform->up() * direction.y() +
                                transform->right() * direction.x())
                               * Time::deltaTimef * speed * shift);

        if (InputManager::getCursorMode() == InputManager::CursorMode::DISABLED) {
            Vector2f mouse = InputManager::getMouseDelta();

            float yaw = mouse.x() * Time::deltaTimef * mouseSensitivity;
            float pitch = mouse.y() * Time::deltaTimef * mouseSensitivity;

            Quaternion q1(transform->right(), pitch);
            Quaternion q2(Vector3f::UP, yaw);

            if (yaw != 0 && pitch != 0) {
                transform->setRotation(transform->getRotation() * q1 * q2);
            }
        }

        if (InputManager::keyDown(InputManager::KEY_PAGE_UP))
            Camera::getMainCamera()->setFOV(Camera::getMainCamera()->getFOV() + 0.1f);
        if (InputManager::keyDown(InputManager::KEY_PAGE_DOWN))
            Camera::getMainCamera()->setFOV(Camera::getMainCamera()->getFOV() - 0.1f);
    }
};