//
// Created by Israel on 22/03/2022.
//

#ifndef VOXENGINE_LOGIC_H
#define VOXENGINE_LOGIC_H

#include "ISystem.h"
#include <vector>
#include <string>
#include "../component/Behaviour.h"

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


#endif //VOXENGINE_LOGIC_H
