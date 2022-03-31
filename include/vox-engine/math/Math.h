//
// Created by Israel on 31/03/2022.
//

#ifndef VOXENGINE_MATH_H
#define VOXENGINE_MATH_H

#include "Vector2f.h"
#include "Quaternion.h"

#define PI 3.14159265358979323846

class Math {
    static const Vector2f halton_seq_16[16];

    static float lerp(float a, float b, float percent) {
        return a + percent * (b - a);
    }

    template<typename T>
    static T min(T a, T b) {
        return (((a) < (b)) ? (a) : (b));
    }

    template<typename T>
    static T max(T a, T b) {
        return (((a) > (b)) ? (a) : (b));
    }

    template<typename T>
    static T clamp(T value, T min, T max) {
        return Math::min(Math::max(value, min), max);
    }

    static Vector3f toEulerAngle(Quaternion q) {
        float roll, pitch, yaw;

        // roll (x-axis rotation)
        double sinr = +2.0 * (q.getW() * q.getX() + q.getY() * q.getZ());
        double cosr = +1.0 - 2.0 * (q.getX() * q.getX() + q.getY() * q.getY());
        roll = (float) atan2(sinr, cosr);

        // pitch (y-axis rotation)
        float m = max(-2.0f * (q.getX() * q.getZ() - q.getW() * q.getY()), -1.0f);
        float t = min(m, 1.0f);
        pitch = (float) asin(t);

        // yaw (z-axis rotation)
        double siny = +2.0 * (q.getW() * q.getZ() + q.getX() * q.getY());
        double cosy = +1.0 - 2.0 * (q.getY() * q.getY() + q.getZ() * q.getZ());
        yaw = (float) atan2(siny, cosy);

        return {roll, pitch, yaw};
    }
};

#endif //VOXENGINE_MATH_H
