//
// Created by Israel Santos Vieira (Computer scientist) - All rights reserved
//

#ifndef FP_OPENGL_INPUTMANAGER_H
#define FP_OPENGL_INPUTMANAGER_H

#include "InputKey.h"
#include<vector>
#include <iostream>
using namespace std;
const unsigned char ESCAPE = 27;
const unsigned char ENTER = 32;

class InputManager {
private:
    static InputManager* m_Instance;
    vector<InputKey*> m_Inputs;
    InputManager();
public:
    static InputManager* getInstance();
    void addKey(unsigned char keyCode, string id, bool positive);
    void updateKeys(unsigned char currentKey, bool targetState);
    bool containsKey(unsigned char key);
    InputKey* getKey(unsigned char keyCode);
    InputKey* getKey(string id, bool positive);
};


#endif //FP_OPENGL_INPUTMANAGER_H
