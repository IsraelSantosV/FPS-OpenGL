//
// Created by Israel Santos Vieira on 17/02/2022.
//

#include "headers/InputManager.h"
#define INVALID_KEY '?'

InputManager::InputManager() { }

void InputManager::addKey(char keyCode, string id, bool positive) {
    if(!containsKey(keyCode)) {
        m_Inputs.push_back(InputKey(keyCode, id, positive));
    }
}

void InputManager::updateKeys(char currentKey, bool targetState) {
    for(auto i = m_Inputs.begin(); i != m_Inputs.end(); ++i){
        if(i->getCode() == currentKey || i->getCode() == isupper(currentKey)){
            i->setState(targetState);
        }
    }
}

InputKey InputManager::getKey(char keyCode) {
    for(auto i = m_Inputs.begin(); i != m_Inputs.end(); ++i){
        if(i->getCode() == keyCode || i->getCode() == isupper(keyCode)){
            return *i;
        }
    }

    return InputKey(INVALID_KEY, "", false);
}

bool InputManager::containsKey(char key) {
    for(auto i = m_Inputs.begin(); i != m_Inputs.end(); ++i){
        if(i->getCode() == key || i->getCode() == isupper(key)){
            return true;
        }
    }

    return false;
}

InputKey InputManager::getKey(string id, bool positive) {
    for(auto i = m_Inputs.begin(); i != m_Inputs.end(); ++i){
        if(i->getID() == id && i->isPositive() == positive){
            return *i;
        }
    }

    return InputKey(INVALID_KEY, "", false);
}

bool InputManager::isInvalidKey(InputKey key) {
    return key.getCode() == INVALID_KEY;
}

InputManager* InputManager::m_Instance = nullptr;
InputManager* InputManager::getInstance() {
    if(m_Instance == nullptr){
        m_Instance = new InputManager();
    }

    return m_Instance;
}




