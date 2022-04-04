//
// Created by zetta on 04/04/2022.
//

#ifndef VOXENGINE_VERTEX_H
#define VOXENGINE_VERTEX_H

#include "../math/Vector3f.h"

class Vertex {
public:
    enum AttibLocation {
        POSITION,
        NORMAL,
        COLOR,
        TEXTURECOORD,
        TANGENT,
    };

    Vector3f position;
    Vector3f normal;
    Vector3f color;
    Vector2f uv;
    Vector3f tangent;

    Vertex() {}

    Vertex(Vector3f pos, Vector3f normal, Vector3f col, Vector2f uv) :
            position(pos),
            normal(normal),
            color(col),
            uv(uv) {
    }

    Vertex(Vector3f pos, Vector3f normal, Vector3f col, Vector2f uv, Vector3f tangent) :
            position(pos),
            normal(normal),
            color(col),
            uv(uv),
            tangent(tangent) {
    }
};

#endif //VOXENGINE_VERTEX_H
