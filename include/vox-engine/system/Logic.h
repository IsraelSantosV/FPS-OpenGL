//
// Created by Israel on 05/04/2022.
//

#ifndef VOXENGINE_LOGIC_H
#define VOXENGINE_LOGIC_H

#include "vox-engine/system/ISystem.h"
#include "vox-engine/component/Component.h"

class Behaviour;

class Logic : public ISystem {
public:
    static void addToUpdateList(Behaviour *behaviour);
    static void removeFromList(Behaviour *behaviour);
    static unsigned long int getTickIndex();

    static void tick();
    static void fixedUpdate();
    static void update();
    static void lateUpdate();

    void start() override;
    void reset() override;
    void destroy() override;
private:
    static std::vector<Behaviour*> _behaviourList;
    static unsigned long int _tickIndex;
};

class Behaviour : public Component {
public:
    virtual ~Behaviour() {}
    void init() override;
    void destroy();

    virtual void Start();
    virtual void Update();
    virtual void FixedUpdate();
    virtual void LateUpdate();
    virtual void OnDestroy();
};


#endif //VOXENGINE_LOGIC_H
