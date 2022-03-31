//
// Created by zetta on 30/03/2022.
//

#include "../../include/vox-engine/util/Utils.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void Utils::split(const std::string &line, const std::string &delimiter, std::vector<std::string> &output) {
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

unsigned char* Utils::loadIcon(const std::string& fileName, int& width, int& height) {
    int numComponents;
    unsigned char *data = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4);

    if (data == nullptr){
        Logger::errorln("Unable to load Icon:", fileName);
    }

    return data;
}

void Utils::freeIcon(unsigned char* data) {
    if (data == nullptr) {
        Logger::errorln("Unable to free icon");
        return;
    }

    stbi_image_free(data);
}

