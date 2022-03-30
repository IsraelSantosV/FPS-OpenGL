//
// Created by zetta on 30/03/2022.
//

#include "../include/vox-engine/util/Logger.h"
#include "../include/vox-engine/core/Application.h"

int main(int argc, char* argv[]){
    Logger::infoln("Hello VoxEngine!");

    Application* voxApplication = new Application();
    voxApplication->init();
    voxApplication->run();

    return EXIT_SUCCESS;
}
