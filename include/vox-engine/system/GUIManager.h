//
// Created by Israel on 08/04/2022.
//

#ifndef VOXENGINE_GUIMANAGER_H
#define VOXENGINE_GUIMANAGER_H

#include "vox-engine/system/ISystem.h"
#include "vox-engine/resources/GUI.h"

class GUIManager : public ISystem {
public:
    void start() override;
    void reset() override;
    void destroy() override;

    static void displayGUICallback();
private:
    static bool show_demo_window;
    static void renderGUI();
};


#endif //VOXENGINE_GUIMANAGER_H
