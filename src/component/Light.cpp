//
// Created by Israel on 13/04/2022.
//

#include "vox-engine/component/Light.h"

void Light::changeLightType(Light::LightType type) {
    m_Type = type;
}

void Light::setIntensity(float value) {
    m_Intensity = value;
}
