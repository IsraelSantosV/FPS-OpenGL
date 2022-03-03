//
// Created by israel on 28/02/2022.
//

#ifndef FP_OPENGL_TIME_CPP
#define FP_OPENGL_TIME_CPP
using namespace std;

class Time {
private:
    static float m_DeltaTime;
    static float m_GameTime;
public:
    static void refreshTime(float passedTime){
        float lastFrameTime = m_GameTime;
        m_GameTime += passedTime;
        m_DeltaTime = m_GameTime - lastFrameTime;
    }

    static float deltaTime(){ return m_DeltaTime; }
    static float gameTime() { return m_GameTime; }
};

#endif //FP_OPENGL_TIME_CPP