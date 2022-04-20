//
// Created by Israel on 13/04/2022.
//

#ifndef VOXENGINE_LIGHT_H
#define VOXENGINE_LIGHT_H

#include "vox-engine/component/Component.h"

class Light : public Component {
public:
    enum LightType {
        AMBIENT, DIFFUSE, SPECULAR, PHONG
    };

    void changeLightType(LightType type);
    void setIntensity(float value);

    LightType getLightType() { return m_Type; }
    float getIntensity(){ return m_Intensity; }
private:
    LightType m_Type;
    float m_Intensity;
};


#endif //VOXENGINE_LIGHT_H
