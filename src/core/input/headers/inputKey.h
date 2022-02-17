//
// Created by zetta on 17/02/2022.
//

#include <iostream>
using namespace std;
#ifndef OPENGL_INPUTKEY_H
#define OPENGL_INPUTKEY_H

enum inputState {
    PRESSED,
    RELEASED
};

class inputKey {
private:
    char m_Key;
    string m_ID;
    bool m_Positive;
    bool m_CurrentState;
public:
    inputKey(char key, string id, bool positive);
    void setState(inputState state);
    char getCode();
    string getID();
    bool isPositive();
    inputState getState();
};


#endif //OPENGL_INPUTKEY_H
