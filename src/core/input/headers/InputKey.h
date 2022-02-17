//
// Created by zetta on 17/02/2022.
//

#include <iostream>
using namespace std;
#ifndef OPENGL_INPUTKEY_H
#define OPENGL_INPUTKEY_H

class InputKey {
private:
    char m_Key;
    string m_ID;
    bool m_Positive;
    bool m_IsPressed;
public:
    InputKey(char key, string id, bool positive);
    void setState(bool isPressed);
    char getCode();
    string getID();
    bool isPositive();
    bool isPressed();
};


#endif //OPENGL_INPUTKEY_H
