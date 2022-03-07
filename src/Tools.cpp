//
// Created by Israel Santos Vieira (Computer scientist) - All rights reserved
//

#ifndef FP_OPENGL_TOOLS_CPP
#define FP_OPENGL_TOOLS_CPP
#define TO_RADIANS 3.14/180.0

#include <iostream>
#include <vector>
#include <cmath>
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
        x = 0;
        y = 0;
        z = 0;
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

    double magnitude(){ return sqrt(x*x + y*y + z*z); }

    static double dot(Vector3 a, Vector3 b){
        return (a.x * b.x + a.y * b.y + a.z * b.z);
    }

    static float angle(Vector3 a, Vector3 b){
        double dotValue = dot(a, b);
        double lenSq1 = a.magnitude();
        double lenSq2 = b.magnitude();
        return acos(dotValue / (lenSq1 * lenSq2));
    }

    static Vector3 directionFromAngle(float angleInDegrees){
        return Vector3(sin(angleInDegrees * TO_RADIANS), 0, cos(angleInDegrees * TO_RADIANS));
    }

    static float distance(Vector3 a, Vector3 b){
        return sqrt(pow((b.x - a.x), 2) + pow((b.y - a.y), 2) + pow((b.z - a.z), 2));
    }

    static Vector3 normalize(Vector3 target){
        double magnitude = target.magnitude();
        if(magnitude == 0){
            return ZERO();
        }

        return target / magnitude;
    }

    static const Vector3 ZERO() { return {0,0,0}; }
    static Vector3 ONE() { return {1,1,1}; }
    static Vector3 UP() { return {0,1,0}; }
    static Vector3 DOWN() { return {0,-1,0}; }
    static Vector3 LEFT() { return {-1,0,0}; }
    static Vector3 RIGHT() { return {1,0,0}; }
    static Vector3 FORWARD() { return {0,0,1}; }
    static Vector3 BACKWARD() { return {0,0,-1}; }
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