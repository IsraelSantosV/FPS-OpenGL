//
// Created by Israel on 13/04/2022.
//

#ifndef VOXENGINE_LIGHTMANAGER_H
#define VOXENGINE_LIGHTMANAGER_H

#include "vox-engine/system/ISystem.h"
#include "vox-engine/component/Light.h"
#include "vox-engine/resources/OpenGL.h"

class LightManager : public ISystem {
public:
    void init(Config::Profile profile) override {
        glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_DEPTH_TEST);

        glShadeModel(GL_SMOOTH);

        //AMBIENTE
        AR = 0.2;
        AG = 0.2;
        AB = 0.2;
        //DIFUSAL
        DR = 0.7;
        DG = 0.7;
        DB = 0.7;
        //ESPECULAR
        ER = 1;
        EG = 1;
        EB = 1;
        //POSICAO
        PX = 0;
        PY = 50;
        PZ = 50;
    }

    void start() override { }
    void destroy() override { }

    static void setupLights();
    static void enableLights();
    static void disableLights();
private:
    std::vector<Light> m_Lights;
    static GLfloat AR, AG, AB;
    static GLfloat DR, DG, DB;
    static GLfloat ER, EG, EB;
    static GLfloat PX, PY, PZ;
};


#endif //VOXENGINE_LIGHTMANAGER_H
