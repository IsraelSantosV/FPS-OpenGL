//
// Created by zetta on 30/03/2022.
//

#include "../VoxEngineCore.h"
#include "Scenes/SampleScene.cpp"

int main(int argc, char* argv[]){
    std::map<std::string, Scene*> sceneMap;
    sceneMap["1. SampleScene"] = new SampleScene();

    Application voxApplication;
    voxApplication.init(sceneMap);
    voxApplication.run();
    voxApplication.destroy();

    return EXIT_SUCCESS;
}
