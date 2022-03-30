//
// Created by Israel on 22/03/2022.
//

#include <GL/glut.h>
#include "../../include/vox-engine/core/Application.h"
#include "../../include/vox-engine/util/Logger.h"
#include "../../include/vox-engine/util/GLError.h"
#include "../../include/vox-engine/resources/FilePath.h"

int main(int argc, char* argv[]){
    glVertex3f(1,0,0);
    glCheckError();
    Logger::errorln("Hello World!");

    auto* path = new FilePath("resource/Icon.png");
    Logger::hr();
    Logger::infoln("AbsolutePath: " + path->getAbsolutePath());
    Logger::infoln("Path: " + path->getPath());
    Logger::infoln("Extension: " + path->getExtension());
    Logger::infoln("Name: " + path->getName());
}