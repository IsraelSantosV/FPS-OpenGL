//
// Created by zetta on 30/03/2022.
//

#ifndef VOXENGINE_UTILS_H
#define VOXENGINE_UTILS_H
#include <cstdarg>
#include <cstring>
#include <string>
#include <vector>

namespace Utils {
    void split(const std::string &line, const std::string &delimiter, std::vector <std::string> &output);
}


#endif //VOXENGINE_UTILS_H
