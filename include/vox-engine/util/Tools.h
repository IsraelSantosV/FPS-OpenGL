//
// Created by Israel on 05/04/2022.
//

#ifndef VOXENGINE_TOOLS_H
#define VOXENGINE_TOOLS_H

#include <cstdarg>
#include <cstring>
#include <iostream>
#include <vector>

class Tools {
public:
    static void split(const std::string &line, const std::string &delimiter, std::vector <std::string> &output);
};

#endif //VOXENGINE_TOOLS_H
