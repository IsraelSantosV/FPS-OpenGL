//
// Created by zetta on 30/03/2022.
//

#ifndef VOXENGINE_UTILS_H
#define VOXENGINE_UTILS_H
#include <cstdarg>
#include <cstring>
#include <iostream>
#include <vector>
#include "Logger.h"
#include "zlib.h"
#include "stb_image.h"

namespace Utils {
    void split(const std::string &line, const std::string &delimiter, std::vector <std::string> &output);
    unsigned char* loadIcon(const std::string& fileName, int& width, int& height);
    void freeIcon(unsigned char* data);
}


#endif //VOXENGINE_UTILS_H
