//
// Created by Israel on 05/04/2022.
//

#ifndef VOXENGINE_CONFIG_H
#define VOXENGINE_CONFIG_H

#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <iostream>
#include "vox-engine/util/Logger.h"
#include "vox-engine/util/Tools.h"

class Config {
public:
    struct Profile {
        std::string appName = "VoxEngine";
        int width = 1280;
        int height = 720;
        bool fullscreen = false;
        double frameRate = 60.0;
    };

    static Profile profile;
    const std::string FILE_PATH = "config.cfg";

    void readConfig();
    void createDefault();
};

#endif //VOXENGINE_CONFIG_H
