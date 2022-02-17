//
// Created by zetta on 17/02/2022.
//

#include "headers/inputKey.h"

inputKey::inputKey(char key, string id, bool positive) : m_Key(key), m_ID(id) {
    m_Positive = positive;
    m_CurrentState = RELEASED;
}

void inputKey::setState(inputState state) {
    m_CurrentState = state;
}

inputState inputKey::getState() {
    return static_cast<inputState>(m_CurrentState);
}

char inputKey::getCode() {
    return m_Key;
}

string inputKey::getID() {
    return m_ID;
}

bool inputKey::isPositive() {
    return m_Positive;
}
