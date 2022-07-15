//
// Created by Israel on 13/04/2022.
//

#include "vox-engine/system/LightManager.h"

GLfloat LightManager::AR;
GLfloat LightManager::AG;
GLfloat LightManager::AB;
GLfloat LightManager::DR;
GLfloat LightManager::DG;
GLfloat LightManager::DB;
GLfloat LightManager::ER;
GLfloat LightManager::EG;
GLfloat LightManager::EB;
GLfloat LightManager::PX;
GLfloat LightManager::PY;
GLfloat LightManager::PZ;

void LightManager::setupLights() {
    GLfloat luzAmbiente[4] = { AR, AG, AB,1.0 };
    GLfloat luzEspecular[4] = { ER, EG, EB, 1.0 };
    GLfloat luzDifusa[4] = { DR, DB, DB,1.0 };
    GLfloat posicaoLuz[4] = { PX, PY, PZ, 1.0 };

    // Capacidade de brilho do material
    GLfloat especularidade[4] = { 1.0,1.0,1.0,1.0 };
    GLint especMaterial = 60;

    // Ativa o uso da luz ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
    // Define a refletância do material
    glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
    // Define a concentração do brilho
    glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
    // Define os parâmetros da luz de número 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
}

void LightManager::enableLights() {
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
}

void LightManager::disableLights() {
    AR = 0;
    AG = 0;
    AB = 0;
    //DIFUSAL
    DR = 0;
    DG = 0;
    DB = 0;
    //ESPECULAR
    ER = 0;
    EG = 0;
    EB = 0;
}
