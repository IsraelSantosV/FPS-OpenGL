//
// Created by Israel on 22/03/2022.
//

#ifndef VOXENGINE_CONFIG_H
#define VOXENGINE_CONFIG_H

#include "../util/Logger.h"
#include "../util/Utils.h"

#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <iostream>

class Config {
public:
    struct Profile {
        std::string appName = "VoxEngine";
        int width = 1280;
        int height = 720;
        bool fullscreen = false;
        bool vsync = false;
        float superSampling = 1.0f;
        bool showFPS = false;
        bool fpsProfiling = false;
    };

    static Profile profile;
    const std::string FILE_PATH = "config.cfg";

    void readConfig();
    void createDefault();
};

#endif //VOXENGINE_CONFIG_H
