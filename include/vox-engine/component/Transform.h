//
// Created by Israel on 05/04/2022.
//

#ifndef VOXENGINE_TRANSFORM_H
#define VOXENGINE_TRANSFORM_H

#include "vox-engine/resources/Math.h"
#include "vox-engine/system/Logic.h"

class Transform : public Component {
public:
    void setPosition(vec3 position);
    void setRotation(vec3 rotation);
    void setRotation(quat rotation);
    void setScale(vec3 scale);
    void setParent(Transform *m_Parent);
    void rotate(quat quaternion);
    quat getRotation();
    vec3 getPosition();
    vec3 getScale();

    Transform* getParent();
    std::vector<Transform*> getChildren();
private:
    vec3 m_Position = vec3(0,0,0);
    quat m_Rotation = quat(0,0,0,0);
    vec3 m_Scale = vec3(1,1,1);
    Transform* m_Parent;
    std::vector<Transform*> m_Children;

    void removeChild(Transform* child);
    void setChanged();
};


#endif //VOXENGINE_TRANSFORM_H
