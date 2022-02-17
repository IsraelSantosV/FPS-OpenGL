//
// Created by zetta on 17/02/2022.
//

#include<vector>
#include "InputKey.h"
using namespace std;
#ifndef OPENGL_INPUTMANAGER_H
#define OPENGL_INPUTMANAGER_H

class InputManager {
private:
    static InputManager* m_Instance;
    vector<InputKey> m_Inputs;
    InputManager();
public:
    static InputManager* getInstance();
    void addKey(char keyCode, string id, bool positive);
    void updateKeys(char currentKey, bool targetState);
    bool containsKey(char key);
    InputKey getKey(char keyCode);
    InputKey getKey(string id, bool positive);
    bool isInvalidKey(InputKey key);
};


#endif //OPENGL_INPUTMANAGER_H
