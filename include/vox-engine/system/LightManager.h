//
// Created by Israel on 13/04/2022.
//

#ifndef VOXENGINE_LIGHTMANAGER_H
#define VOXENGINE_LIGHTMANAGER_H

#include "vox-engine/system/ISystem.h"
#include "vox-engine/component/Light.h"

class LightManager : public ISystem {
public:

private:
    std::vector<Light> m_Lights;
};


#endif //VOXENGINE_LIGHTMANAGER_H
