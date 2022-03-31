//
// Created by Israel on 22/03/2022.
//

#ifndef VOXENGINE_LOGIC_H
#define VOXENGINE_LOGIC_H

#include "ISystem.h"
#include "IBehaviour.h"
#include <vector>
#include <string>

class Logic : public ISystem {
public:
    static void addToUpdateList(IBehaviour *behaviour);
    static void removeFromList(IBehaviour *behaviour);
    static unsigned long int getTickIndex();

    static void tick();
    static void fixedUpdate();
    static void update();
    static void lateUpdate();

    void start() override;
    void reset() override;
    void destroy() override;
private:
    static std::vector<IBehaviour*> _behaviourList;
    static unsigned long int _tickIndex;
};


#endif //VOXENGINE_LOGIC_H
