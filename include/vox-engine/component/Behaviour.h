//
// Created by Israel on 22/03/2022.
//

#ifndef VOXENGINE_BEHAVIOUR_H
#define VOXENGINE_BEHAVIOUR_H

#include "Component.h"

class Behaviour : public Component {
public:
    virtual ~Behaviour();
    virtual void Start();
    virtual void Update();
    virtual void FixedUpdate();
    virtual void LateUpdate();
    virtual void OnDestroy();
};


#endif //VOXENGINE_BEHAVIOUR_H
