//
// Created by zetta on 07/04/2022.
//

#include "vox-engine/core.h"

class CubeAnimation : public Behaviour {
private:
    double m_Timer = 0;
    double m_CurrentAmount = 0;
    bool m_CurrentSide = true;
public:
    double interval = 0.001;
    double amount = 0.05;
    double maxSideAmount = 2;

    void Update() override {
        m_Timer += Time::deltaTime;

        if(m_Timer >= interval){
            m_Timer = 0;

            m_CurrentAmount += amount;
            if(m_CurrentAmount >= maxSideAmount){
                m_CurrentAmount = 0;
                m_CurrentSide = !m_CurrentSide;
            }

            int sideMultiplier = m_CurrentSide ? 1 : -1;
            vec3 currentPos = getEntity()->transform->getPosition();
            vec3 targetPos = vec3(currentPos.x + (amount * sideMultiplier), currentPos.y, currentPos.z);
            getEntity()->transform->setPosition(targetPos);
        }
    }
};