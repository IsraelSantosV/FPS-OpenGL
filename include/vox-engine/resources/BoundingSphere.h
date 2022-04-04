//
// Created by zetta on 01/04/2022.
//

#ifndef VOXENGINE_BOUNDINGSPHERE_H
#define VOXENGINE_BOUNDINGSPHERE_H

#include "../math/Vector3f.h"

class BoundingSphere {
public:
    BoundingSphere() {}
    BoundingSphere(Vector3f center, float radius): _center(center), _radius(radius) {}
    Vector3f getCenter() { return _center; };
    float getRadius() { return _radius; }
private:
    Vector3f _center;
    float _radius;
};

#endif //VOXENGINE_BOUNDINGSPHERE_H
