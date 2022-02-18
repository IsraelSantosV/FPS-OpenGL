//
// Created by Israel Santos Vieira on 17/02/2022.
//

#include<vector>
#include "InputKey.h"
using namespace std;
#ifndef OPENGL_INPUTMANAGER_H
#define OPENGL_INPUTMANAGER_H
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


#endif //OPENGL_INPUTMANAGER_H
