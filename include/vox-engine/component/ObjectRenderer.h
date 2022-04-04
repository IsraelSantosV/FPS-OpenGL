//
// Created by zetta on 01/04/2022.
//

#ifndef VOXENGINE_OBJECTRENDERER_H
#define VOXENGINE_OBJECTRENDERER_H

#include "../util/Utils.h"
#include "Component.h"
#include "../resources/BoundingSphere.h"

class ObjectRenderer : public Component {
public:
    bool getReflected = true;
    bool castShadows = true;

    virtual ~ObjectRenderer() {}

    virtual void init();
    virtual void render() = 0;
    virtual void onDestroy();
    virtual BoundingSphere getBoundingSphere();

    void destroy();
    RenderType getType() { return _type; }
    void setRenderType(RenderType type);

    //void setMaterial(Material* material) { _material = material; }
    //Material* getMaterial() { return _material; }
protected:
    RenderType _type;
    //Material* _material;
};


#endif //VOXENGINE_OBJECTRENDERER_H
