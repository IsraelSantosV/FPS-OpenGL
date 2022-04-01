//
// Created by zetta on 30/03/2022.
//

#ifndef VOXENGINE_RESOURCES_H
#define VOXENGINE_RESOURCES_H

#define BUILD_MODE false
#include <string>

namespace Resources {
#if BUILD_MODE
    const std::string ENGINE_RESOURCES = "./resources";
#else
    const std::string ENGINE_RESOURCES = "./ve_resources";
#endif
};

#endif //VOXENGINE_RESOURCES_H
