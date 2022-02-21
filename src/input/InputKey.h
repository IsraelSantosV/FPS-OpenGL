//
// Created by Israel Santos Vieira (Computer scientist) - All rights reserved
//

#ifndef FP_OPENGL_INPUTKEY_H
#define FP_OPENGL_INPUTKEY_H

#include <iostream>
#include <vector>
using namespace std;

typedef void Action();

enum ActionTriggerMode {
    ONE_TIME,
    REPEATEDLY
};

struct TriggerAction {
    Action* action = nullptr;
    ActionTriggerMode mode = ONE_TIME;
    bool validTrigger = false;
    bool readForUse = true;
};

class InputKey {
private:
    unsigned char m_Key;
    string m_ID;
    bool m_Positive;
    bool m_IsPressed;
    vector<TriggerAction*> m_Actions;
public:
    InputKey(unsigned char key, string id, bool positive);
    void setState(bool isPressed);
    void registerAction(Action action, ActionTriggerMode mode);
    void triggerActions();
    void refreshActions();
    unsigned char getCode();
    string getID();
    bool isPositive();
    bool isPressed();
};


#endif //FP_OPENGL_INPUTKEY_H
