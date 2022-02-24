//
// Created by Israel Santos Vieira (Computer scientist) - All rights reserved
//

#ifndef FP_OPENGL_INPUTMANAGER_CPP
#define FP_OPENGL_INPUTMANAGER_CPP

#include<vector>
#include <iostream>
#include "Debug.cpp"
using namespace std;
const unsigned char ESCAPE = 27;
const unsigned char SPACE = 32;
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
    InputKey(unsigned char key, string id, bool positive){
        m_Key = key;
        m_ID = id;
        m_Positive = positive;
        m_IsPressed = false;
    }

    void setState(bool isPressed){ m_IsPressed = isPressed; }

    void registerAction(Action action, ActionTriggerMode mode){
        auto* trigger = new TriggerAction();
        trigger->action = action;
        trigger->validTrigger = action != nullptr;
        trigger->mode = mode;
        trigger->readForUse = true;
        m_Actions.push_back(trigger);
    }

    void triggerActions(){
        for(auto i = m_Actions.begin(); i != m_Actions.end(); ++i){
            auto element = *i;
            if(!element->validTrigger || !element->readForUse) continue;
            (*element->action)();

            if(element->mode == ONE_TIME){
                element->readForUse = false;
            }
        }
    }

    void refreshActions(){
        for(auto i = m_Actions.begin(); i != m_Actions.end(); ++i){
            auto element = *i;
            element->readForUse = true;
        }
    }

    unsigned char getCode() { return m_Key; }
    string getID() { return m_ID; }
    bool isPositive() { return m_Positive; }
    bool isPressed(){ return m_IsPressed; }
};

class InputManager {
private:
    static InputManager* m_Instance;
    vector<InputKey*> m_Inputs;
    InputManager(){
        Debug::log("[1/5] Loading InputManager and define symbols...");
    }
public:
    static InputManager* getInstance(){
        if(m_Instance == nullptr){
            m_Instance = new InputManager();
        }

        return m_Instance;
    }

    void addKey(unsigned char keyCode, string id, bool positive){
        if(!containsKey(keyCode)) {
            m_Inputs.push_back(new InputKey(keyCode, id, positive));
        }
    }

    void updateKeys(unsigned char currentKey, bool targetState){
        for(auto i = m_Inputs.begin(); i != m_Inputs.end(); ++i){
            auto element = *i;
            if(element->getCode() == currentKey){
                element->setState(targetState);

                if(targetState){
                    element->triggerActions();
                }
                else {
                    element->refreshActions();
                }
            }
        }
    }

    bool containsKey(unsigned char key){
        for(auto i = m_Inputs.begin(); i != m_Inputs.end(); ++i){
            auto element = *i;
            if(element->getCode() == key){
                return true;
            }
        }

        return false;
    }

    InputKey* getKey(unsigned char keyCode){
        for(auto i = m_Inputs.begin(); i != m_Inputs.end(); ++i){
            auto element = *i;
            if(element->getCode() == keyCode){
                return element;
            }
        }

        return nullptr;
    }

    InputKey* getKey(string id, bool positive){
        for(auto i = m_Inputs.begin(); i != m_Inputs.end(); ++i){
            auto element = *i;
            if(element->getID() == id && element->isPositive() == positive){
                return *i;
            }
        }

        return nullptr;
    }
};

#endif //FP_OPENGL_INPUTMANAGER_CPP