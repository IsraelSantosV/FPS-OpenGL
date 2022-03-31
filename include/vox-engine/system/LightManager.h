//
// Created by Israel on 22/03/2022.
//

#ifndef VOXENGINE_LIGHTMANAGER_H
#define VOXENGINE_LIGHTMANAGER_H

#include "ISystem.h"

class LightManager : public ISystem {
public:
    void start() override;
    void destroy() override;
};


#endif //VOXENGINE_LIGHTMANAGER_H
