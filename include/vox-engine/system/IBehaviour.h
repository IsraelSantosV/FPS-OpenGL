//
// Created by Israel on 30/03/2022.
//

#ifndef VOXENGINE_IBEHAVIOUR_H
#define VOXENGINE_IBEHAVIOUR_H

#include "Component.h"

class IBehaviour : public Component {
public:
    virtual ~IBehaviour();
    virtual void Start();
    virtual void Update();
    virtual void FixedUpdate();
    virtual void LateUpdate();
    virtual void OnDestroy();
};

#endif //VOXENGINE_IBEHAVIOUR_H
