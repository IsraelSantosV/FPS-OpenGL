//
// Created by Israel on 05/04/2022.
//

#include "vox-engine/core.h"

class Health : public Behaviour {
public:
    float currentHealth;
    double timer;
    const float timeToTakeHealth = 4;

    void Start(){
        timer = 0;
        currentHealth = 100;
    }

    void Update(){
        if(currentHealth <= 0) return;
        timer += Time::deltaTime;

        if(timer >= timeToTakeHealth) {
            currentHealth -= 1;
            timer = 0;
            Logger::infoln("CurrentHealth: " + std::to_string(currentHealth));
        }
    }

};
