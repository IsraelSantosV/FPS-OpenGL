//
// Created by Israel on 05/04/2022.
//

#include "vox-engine/core.h"
#include "Scenes/MainScene.cpp"

int main(int argc, char* argv[]){
    std::map<std::string, Scene*> sceneMaps;
    sceneMaps["MainScene"] = new MainScene();

    Application engine;
    engine.init(sceneMaps, argc, argv);
    engine.start();

    return EXIT_SUCCESS;
}