//
// Created by zetta on 17/02/2022.
//

#include "headers/inputManager.h"
#define INVALID_KEY '?'

inputManager::inputManager() {
    m_Inputs = new vector<inputKey>();
}

inputManager::~inputManager() {
    delete m_Inputs;
}

void inputManager::addKey(char keyCode, string id, bool positive) {
    if(!containsKey(keyCode)) {
        m_Inputs->push_back(inputKey(keyCode, id, positive));
    }
}

void inputManager::updateKeys(char currentKey, inputState targetState) {
    for(auto i = m_Inputs->begin(); i != m_Inputs->end(); ++i){
        if(i->getCode() == currentKey || i->getCode() == isupper(currentKey)){
            i->setState(targetState);
        }
    }
}

inputKey inputManager::getKey(char keyCode) {
    for(auto i = m_Inputs->begin(); i != m_Inputs->end(); ++i){
        if(i->getCode() == keyCode || i->getCode() == isupper(keyCode)){
            return *i;
        }
    }

    return inputKey(INVALID_KEY, "", false);
}

bool inputManager::containsKey(char key) {
    for(auto i = m_Inputs->begin(); i != m_Inputs->end(); ++i){
        if(i->getCode() == key || i->getCode() == isupper(key)){
            return true;
        }
    }

    return false;
}

inputKey inputManager::getKey(string id, bool positive) {
    for(auto i = m_Inputs->begin(); i != m_Inputs->end(); ++i){
        if(i->getID() == id && i->isPositive() == positive){
            return *i;
        }
    }

    return inputKey(INVALID_KEY, "", false);
}

bool inputManager::isInvalidKey(inputKey key) {
    return key.getCode() == INVALID_KEY;
}




