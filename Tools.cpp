//
// Created by Israel Santos Vieira (Computer scientist) - All rights reserved
//

#ifndef FP_OPENGL_TOOLS_CPP
#define FP_OPENGL_TOOLS_CPP
#include "Models.cpp"

class Vector3 {
public:
    float x;
    float y;
    float z;

    Vector3(){
        x, y, z = 0;
    }

    Vector3(float _x, float _y, float _z){
        x = _x;
        y = _y;
        z = _z;
    }
    Vector3(float _x, float _y){
        x = _x;
        y = _y;
        z = 0;
    }

    void set(float _x, float _y, float _z){
        x = _x;
        y = _y;
        z = _z;
    }
};

//Random static class
class Random {
private:
    Random() { } //Disable constructor
    static int RANDOM_ID;
public:
    static int getNextID(){
        if(RANDOM_ID < 0){
            RANDOM_ID = 0;
        }

        return ++RANDOM_ID;
    }
};

#endif //FP_OPENGL_TOOLS_CPP