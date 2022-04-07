//
// Created by Israel Santos Vieira (Computer scientist) - All rights reserved
//

#include "vox-engine/util/Tools.h"

void Tools::split(const std::string &line, const std::string &delimiter, std::vector<std::string> &output) {
    std::string s = line;
    size_t pos = 0;
    std::string token;

    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        output.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    output.push_back(s);
}

/*
//When add layer, update layer count
const int LayersAmount = 5;
enum Layer {
    DEFAULT = 0,
    GROUND = 1,
    OBSTACLE = 2,
    PLAYER = 3,
    NO_COLLISION = 4
};

struct LayerData {
    Layer targetLayer;
    bool collisions[LayersAmount];
};

class LayerMatrix {
private:
    LayerData m_LayerMatrix[LayersAmount];
    static LayerMatrix* m_Instance;

    LayerMatrix() {
        for(int i = 0; i < LayersAmount; i++){
            m_LayerMatrix[i].targetLayer = static_cast<Layer>(i);

            for(int j = 0; j < LayersAmount; j++){
                m_LayerMatrix[i].collisions[j] = false;
            }
        }
    }

    bool containsRule(Layer layerA, Layer layerB){
        return m_LayerMatrix[layerA].collisions[layerB] ||
               m_LayerMatrix[layerB].collisions[layerA];
    }
public:
    static LayerMatrix* getInstance(){
        if(m_Instance == nullptr){
            m_Instance = new LayerMatrix();
        }

        return m_Instance;
    }

    void initialize(){ }

    void addRule(Layer fromLayer, Layer targetLayer){
        m_LayerMatrix[fromLayer].collisions[targetLayer] = true;
        m_LayerMatrix[targetLayer].collisions[fromLayer] = true;
    }

    void removeRule(Layer fromLayer, Layer targetLayer){
        m_LayerMatrix[fromLayer].collisions[targetLayer] = false;
        m_LayerMatrix[targetLayer].collisions[fromLayer] = false;
    }

    void addToEverything(Layer targetLayer){
        for(int i = 0; i < LayersAmount; i++){
            m_LayerMatrix[i].collisions[targetLayer] = true;
        }
    }

    void removeToEverything(Layer targetLayer){
        for(int i = 0; i < LayersAmount; i++){
            m_LayerMatrix[i].collisions[targetLayer] = false;
        }
    }

    void clearLayer(Layer targetLayer){
        for(int i = 0; i < LayersAmount; i++){
            m_LayerMatrix[targetLayer].collisions[i] = false;
        }

        removeToEverything(targetLayer);
    }

    bool canApplyPhysics(Layer layerA, Layer layerB){
        return containsRule(layerA, layerB);
    }
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
};*/