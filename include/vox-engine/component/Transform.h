//
// Created by Israel on 05/04/2022.
//

#ifndef VOXENGINE_TRANSFORM_H
#define VOXENGINE_TRANSFORM_H

#include "vox-engine/math/Quaternion.h"
#include "vox-engine/math/Vector3.h"
#include "vox-engine/system/Logic.h"

class Transform : public Component {
public:
    void setPosition(Vector3 position);
    void setRotation(Vector3 rotation);
    void setRotation(Quaternion rotation);
    void setScale(Vector3 scale);
    void setParent(Transform *m_Parent);
    void rotate(Quaternion quaternion);
    Quaternion getRotation();
    Vector3 getPosition();
    Vector3 getScale();

    Transform* getParent();
    std::vector<Transform*> getChildren();
private:
    Vector3 m_Position = Vector3::ZERO;
    Quaternion m_Rotation = Quaternion::ZERO;
    Vector3 m_Scale = Vector3::ONE;
    Transform* m_Parent;
    std::vector<Transform*> m_Children;

    void removeChild(Transform* child);
    void setChanged();
};


#endif //VOXENGINE_TRANSFORM_H
