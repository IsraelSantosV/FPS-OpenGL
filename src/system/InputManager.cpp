//
// Created by Israel Santos Vieira (Computer scientist) - All rights reserved
//

#include "vox-engine/system/InputManager.h"

std::vector<int> InputManager::_keyPress;
std::vector<int> InputManager::_keyDown;
std::vector<int> InputManager::_keyRelease;
float InputManager::_xPos = 0;
float InputManager::_yPos = 0;
float InputManager::_xPosLast = 0;
float InputManager::_yPosLast = 0;

void InputManager::init(Config::Profile profile) {
    Logger::infoln("Initializing InputManager");

    _xPos = 0;
    _yPos = 0;
    _xPosLast = 0;
    _yPosLast = 0;

    glutPassiveMotionFunc(InputManager::passiveMotionCallback);
    glutKeyboardFunc(InputManager::keyboardDownCallback);
    glutKeyboardUpFunc(InputManager::keyboardUpCallback);
    glutIgnoreKeyRepeat(true);
}

bool InputManager::keyPressed(int key) {
    for (int _keyPres: _keyPress) {
        if (_keyPres == key) return true;
    }

    return false;
}

bool InputManager::keyDown(int key) {
    for (int i : _keyDown) {
        if (i == key) return true;
    }

    return false;
}

bool InputManager::keyReleased(int key) {
    for (int i : _keyRelease) {
        if (i == key) return true;
    }

    return false;
}

Vector3 InputManager::getMouse() {
    float x = (_xPos - Display::getWidth() / 2.0f) / Display::getWidth() * 2.0f;
    float y = (_yPos - Display::getHeight() / 2.0f) / Display::getHeight() * -2.0f;
    return {x, y, 0};
}

Vector3 InputManager::getMouseDelta() {
    float xl = (_xPosLast - Display::getWidth() / 2.0f) / Display::getWidth() * 2.0f;
    float yl = (_yPosLast - Display::getHeight() / 2.0f) / Display::getHeight() * -2.0f;
    float x = (_xPos - Display::getWidth() / 2.0f) / Display::getWidth() * 2.0f;
    float y = (_yPos - Display::getHeight() / 2.0f) / Display::getHeight() * -2.0f;
    float xRes = (x - xl) / (Time::deltaTime == 0 ? 0.001f : Time::deltaTime);
    float yRes = (y - yl) / (Time::deltaTime == 0 ? 0.001f : Time::deltaTime);

    return {xRes, yRes, 0};
}

void InputManager::handleKey(int key, int action) {
    if (action == PRESSED) {
        _keyPress.push_back(key);
        _keyDown.push_back(key);
    }
    else if (action == RELEASED) {
        _keyDown.erase(std::remove(_keyDown.begin(), _keyDown.end(), key), _keyDown.end());
        _keyRelease.push_back(key);
    }
}

void InputManager::handleMouse(float x, float y) {
    _xPos = x;
    _yPos = y;
}

void InputManager::update() {
    _xPosLast = _xPos;
    _yPosLast = _yPos;
    _keyPress.clear();
    _keyRelease.clear();
}

void InputManager::keyboardUpCallback(unsigned char key, int x, int y) {
    InputManager::handleKey(key, RELEASED);
}

void InputManager::keyboardDownCallback(unsigned char key, int x, int y) {
    InputManager::handleKey(key, PRESSED);
}

void InputManager::passiveMotionCallback(int x, int y) {
    InputManager::handleMouse((float)x, (float)y);
}