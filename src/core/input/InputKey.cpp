//
// Created by Israel Santos Vieira on 17/02/2022.
//

#include "headers/InputKey.h"

InputKey::InputKey(unsigned char key, string id, bool positive) : m_Key(key), m_ID(id) {
    m_Positive = positive;
    m_IsPressed = false;
}

void InputKey::setState(bool isPressed) {
    m_IsPressed = isPressed;
}

bool InputKey::isPressed() {
    return m_IsPressed;
}

unsigned char InputKey::getCode() {
    return m_Key;
}

string InputKey::getID() {
    return m_ID;
}

bool InputKey::isPositive() {
    return m_Positive;
}

void InputKey::registerAction(Action action, ActionTriggerMode mode) {
    auto* trigger = new TriggerAction();
    trigger->action = action;
    trigger->validTrigger = action != nullptr;
    trigger->mode = mode;
    trigger->readForUse = true;
    m_Actions.push_back(trigger);
}

void InputKey::triggerActions() {
    for(auto i = m_Actions.begin(); i != m_Actions.end(); ++i){
        auto element = *i;
        if(!element->validTrigger || !element->readForUse) continue;
        (*element->action)();

        if(element->mode == ONE_TIME){
            element->readForUse = false;
        }
    }
}

void InputKey::refreshActions() {
    for(auto i = m_Actions.begin(); i != m_Actions.end(); ++i){
        auto element = *i;
        element->readForUse = true;
    }
}
