//
// Created by Israel on 22/03/2022.
//

#include "../../include/vox-engine/core/Config.h"

Config::Profile Config::profile;

void Config::readConfig() {
    std::ifstream file(FILE_PATH);
    std::string line;
    std::vector<std::string> tokens;

    if (file.fail()) {
        Logger::infoln("Creating new config file.");
        createDefault();

        return;
    }

    while (std::getline(file, line)) {
        tokens.clear();
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        Utils::split(line, "=", tokens);

        if (tokens[0].empty() || tokens[0].at(0) == '#') {
            continue;
        } else if (tokens[0] == "appName") {
            profile.appName = tokens[1];
        } else if (tokens[0] == "width") {
            profile.width = std::stoi(tokens[1]);
        } else if (tokens[0] == "height") {
            profile.height = std::stoi(tokens[1]);
        } else if (tokens[0] == "fullscreen") {
            profile.fullscreen = (bool) std::stoi(tokens[1]);
        } else if (tokens[0] == "vsync") {
            profile.vsync = (bool) std::stoi(tokens[1]);
        } else if (tokens[0] == "superSampling") {
            profile.superSampling = (float) std::stof(tokens[1]);
        } else if (tokens[0] == "show_fps") {
            profile.showFPS = (bool) std::stoi(tokens[1]);
        } else if (tokens[0] == "fps_profiling") {
            profile.fpsProfiling = (bool) std::stoi(tokens[1]);
        } else {
            Logger::warnln("Unknown token:", tokens[0]);
        }
    }

    file.close();
}

void Config::createDefault() {
    Profile def;
    std::string str = "#Vox Engine configuration file\n"
                    "appName = " + def.appName + "\n"
                    "width = " + std::to_string(def.width) + "\n"
                    "height = " + std::to_string(def.height) + "\n"
                    "fullscreen = " + std::to_string(def.fullscreen) + "\n"
                    "vsync = " + std::to_string(def.vsync) + "\n"
                    "superSampling = " + std::to_string(def.superSampling) + "\n"
                    "show_fps = " + std::to_string(def.showFPS) + "\n"
                    "fps_profiling = " + std::to_string(def.fpsProfiling) + "\n";

    std::ofstream file(FILE_PATH);
    file << str;
    file.close();
}
