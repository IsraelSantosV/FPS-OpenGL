//
// Created by Israel on 08/04/2022.
//

#ifndef VOXENGINE_GUIMANAGER_H
#define VOXENGINE_GUIMANAGER_H

#include <utility>

#include "vox-engine/system/ISystem.h"
#include "vox-engine/resources/GUI.h"
#include "vox-engine/system/Entity.h"
#include "vox-engine/system/Display.h"
#include "vox-engine/component/Camera.h"

class GUIManager : public ISystem {
public:
    void start() override;
    void reset() override;
    void destroy() override;

    static void displayGUICallback(std::vector<Entity*> sceneObjects);
private:
    static bool show_demo_window;
    static void renderGUI(std::vector<Entity*> sceneObjects);
    static void renderInspector();
    static void renderHierarchy(std::vector<Entity*> sceneObjects);
    static void drawHierarchyNode(Entity* entity);
    static void drawNodeComponents(Entity* entity);
    static bool isSelectedEntity(Entity* entity);

    static Entity* m_SelectedEntity;
};


#endif //VOXENGINE_GUIMANAGER_H
