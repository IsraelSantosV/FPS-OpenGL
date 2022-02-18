//
// Created by Israel Santos Vieira on 17/02/2022.
//

#include "headers/InputManager.h"

InputManager::InputManager() { }

void InputManager::addKey(unsigned char keyCode, string id, bool positive) {
    if(!containsKey(keyCode)) {
        m_Inputs.push_back(new InputKey(keyCode, id, positive));
    }
}

void InputManager::updateKeys(unsigned char currentKey, bool targetState) {
    for(auto i = m_Inputs.begin(); i != m_Inputs.end(); ++i){
        auto element = *i;
        if(element->getCode() == currentKey){
            element->setState(targetState);

            if(targetState){
                element->triggerActions();
            }
            else {
                element->refreshActions();
            }
        }
    }
}

InputKey* InputManager::getKey(unsigned char keyCode) {
    for(auto i = m_Inputs.begin(); i != m_Inputs.end(); ++i){
        auto element = *i;
        if(element->getCode() == keyCode){
            return element;
        }
    }

    return nullptr;
}

bool InputManager::containsKey(unsigned char key) {
    for(auto i = m_Inputs.begin(); i != m_Inputs.end(); ++i){
        auto element = *i;
        if(element->getCode() == key){
            return true;
        }
    }

    return false;
}

InputKey* InputManager::getKey(string id, bool positive) {
    for(auto i = m_Inputs.begin(); i != m_Inputs.end(); ++i){
        auto element = *i;
        if(element->getID() == id && element->isPositive() == positive){
            return *i;
        }
    }

    return nullptr;
}

InputManager* InputManager::m_Instance = nullptr;
InputManager* InputManager::getInstance() {
    if(m_Instance == nullptr){
        m_Instance = new InputManager();
    }

    return m_Instance;
}




