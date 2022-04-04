//
// Created by zetta on 01/04/2022.
//

#ifndef VOXENGINE_CUSTOMMESH_H
#define VOXENGINE_CUSTOMMESH_H

#include "ObjectRenderer.h"
typedef void RenderMesh();

class CustomMesh : public ObjectRenderer {
public:
    CustomMesh() = default;
    explicit CustomMesh(RenderMesh meshAction){
        setMesh(meshAction);
    }

    void setMesh(RenderMesh meshAction){
        _renderAction = meshAction;
    }

    void render() override {
        if(_renderAction != nullptr){
            _renderAction();
        }
    }
private:
    RenderMesh* _renderAction;
};


#endif //VOXENGINE_CUSTOMMESH_H
