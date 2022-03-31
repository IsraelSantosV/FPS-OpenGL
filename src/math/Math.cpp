//
// Created by Israel on 31/03/2022.
//

#include "../../include/vox-engine/math/Math.h"

const Vector2f Math::halton_seq_16[16] = {
        Vector2f(0.00398f, 0.99203f),
        Vector2f(0.49402f, 0.66002f),
        Vector2f(0.24501f, 0.32802f),
        Vector2f(0.74302f, 0.88136f),
        Vector2f(0.12051f, 0.54935f),
        Vector2f(0.61852f, 0.21735f),
        Vector2f(0.36952f, 0.77069f),
        Vector2f(0.86752f, 0.43868f),
        Vector2f(0.05826f, 0.10668f),
        Vector2f(0.55627f, 0.95514f),
        Vector2f(0.30727f, 0.62313f),
        Vector2f(0.80527f, 0.29113f),
        Vector2f(0.18276f, 0.84447f),
        Vector2f(0.68077f, 0.51246f),
        Vector2f(0.43177f, 0.18046f),
        Vector2f(0.92978f, 0.73380f),
};
