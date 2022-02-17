//
// Created by zetta on 17/02/2022.
//

#include "headers/InputKey.h"

InputKey::InputKey(char key, string id, bool positive) : m_Key(key), m_ID(id) {
    m_Positive = positive;
    m_IsPressed = false;
}

void InputKey::setState(bool isPressed) {
    m_IsPressed = isPressed;
}

bool InputKey::isPressed() {
    return m_IsPressed;
}

char InputKey::getCode() {
    return m_Key;
}

string InputKey::getID() {
    return m_ID;
}

bool InputKey::isPositive() {
    return m_Positive;
}
