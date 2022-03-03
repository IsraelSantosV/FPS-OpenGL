//
// Created by Israel Santos Vieira (Computer scientist) - All rights reserved
//

#ifndef FP_OPENGL_TOOLS_CPP
#define FP_OPENGL_TOOLS_CPP

#include <iostream>
#include <vector>
using namespace std;

enum Layer {
    DEFAULT,
    GROUND,
    OBSTACLE,
    PLAYER
};

class LayerMask {
public:
    explicit LayerMask(Layer layers[], bool detectWhatever = true){
        detectAnOccurrence = detectWhatever;
        int size = (sizeof(layers)/sizeof(*layers));

        for(int i = 0; i < size; i++){
            targets.push_back(layers[i]);
        }
    }

    vector<Layer> targets;
    bool detectAnOccurrence;
};

class Layers {
public:
    static bool layerInLayerMask(Layer layer, LayerMask* mask){
        if(mask == nullptr) return false;
        for(auto target : mask->targets){
            if(target == layer && mask->detectAnOccurrence) return true;
            else if(target != layer && !mask->detectAnOccurrence) return false;
        }

        return false;
    }
};

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

    string toString(){ return '(' + to_string(x) + ',' +
                        to_string(y) + ',' + to_string(z) + ')'; };

    bool equals(Vector3 otherVector){
        return otherVector.x == x && otherVector.y == y && otherVector.z == z;
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