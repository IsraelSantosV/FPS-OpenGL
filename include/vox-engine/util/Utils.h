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

enum RenderType {
    RT_OPAQUE, RT_CUTOUT, RT_TRANSPARENT
};

class Utils {
public:
    static void split(const std::string &line, const std::string &delimiter, std::vector <std::string> &output);
    static unsigned char* loadIcon(const std::string& fileName, int& width, int& height);
    static void freeIcon(unsigned char* data);
};

#endif //VOXENGINE_UTILS_H
