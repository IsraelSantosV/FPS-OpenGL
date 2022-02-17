//
// Created by zetta on 17/02/2022.
//

#include<vector>
#include "inputKey.h"
using namespace std;
#ifndef OPENGL_INPUTMANAGER_H
#define OPENGL_INPUTMANAGER_H


class inputManager {
private:
    vector<inputKey>* m_Inputs;
    inputManager();
public:
    static inputManager& getInstance();
    void addKey(char keyCode, string id, bool positive);
    void updateKeys(char currentKey, inputState targetState);
    bool containsKey(char key);
    inputKey getKey(char keyCode);
    inputKey getKey(string id, bool positive);
    bool isInvalidKey(inputKey key);
};


#endif //OPENGL_INPUTMANAGER_H
