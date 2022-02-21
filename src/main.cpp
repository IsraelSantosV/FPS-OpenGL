#include <GL/glut.h>
#include "controllers/Camera.h"
#include "controllers/Scenario.h"
#include "input/InputManager.h"

#define FPS 60

//Width and height of the window (Aspect ratio 16:9)
const int sceneScale = 100;
const int width = 16*sceneScale;
const int height = 9*sceneScale;

void display();
void reshape(int w,int h);
void timer(int);
void passive_motion(int,int);
void keyboard(unsigned char key,int x,int y);
void keyboard_up(unsigned char key,int x,int y);

void init(){
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    Camera::getInstance()->initialize(5, 10);
    Camera::getInstance()->setScreenSize(width, height);
    Camera::getInstance()->setVerticalLimit(Vector3(70, 60, 0));
    Camera::getInstance()->setCursorLockState(true);
    Camera::getInstance()->registerActionTriggers();
}

void setupInputs(){
    InputManager::getInstance()->addKey('w', "Vertical", true);
    InputManager::getInstance()->addKey('s', "Vertical", false);
    InputManager::getInstance()->addKey('a', "Horizontal", false);
    InputManager::getInstance()->addKey('d', "Horizontal", true);
    InputManager::getInstance()->addKey(ESCAPE, "Escape", true);
}

void draw(){
    glEnable(GL_TEXTURE_2D);
    glColor4f(1,1,1,1);
    GLuint texture;
    glGenTextures(1,&texture);

    unsigned char texture_data[2][2][4] =
            {
                    0,0,0,255,  255,255,255,255,
                    255,255,255,255,    0,0,0,255
            };

    glBindTexture(GL_TEXTURE_2D,texture);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,2,2,0,GL_RGBA,GL_UNSIGNED_BYTE,texture_data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);

    glBegin(GL_QUADS);

    glTexCoord2f(0.0,0.0);  glVertex3f(-50.0,-5.0,-50.0);
    glTexCoord2f(25.0,0.0);  glVertex3f(50.0,-5.0,-50.0);
    glTexCoord2f(25.0,25.0);  glVertex3f(50.0,-5.0,50.0);
    glTexCoord2f(0.0,25.0);  glVertex3f(-50.0,-5.0,50.0);

    glEnd();
    glDisable(GL_TEXTURE_2D);

    Scenario::getInstance()->drawScenario();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    Camera::getInstance()->updateMovement();
    draw();
    glutSwapBuffers();
}

void reshape(int w,int h){
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,16.0/9.0,1,75);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int){
    glutPostRedisplay();

    if(Camera::getInstance()->cursorIsLocked()){
        glutWarpPointer(width/2,height/2);
    }

    glutTimerFunc(1000/FPS,timer,0);
}

void passive_motion(int x,int y){
    int dev_x,dev_y;
    dev_x = (width/2)-x;
    dev_y = (height/2)-y;
    Camera::getInstance()->receiveMousePosition(dev_x, dev_y);
}

void keyboard(unsigned char key,int x,int y){
    InputManager::getInstance()->updateKeys(key, true);
}

void keyboard_up(unsigned char key,int x,int y){
    InputManager::getInstance()->updateKeys(key, false);
}

int main(int argc,char**argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("FP 3D Simulation");

    setupInputs();
    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0,timer,0);
    glutPassiveMotionFunc(passive_motion);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboard_up);
    glutIgnoreKeyRepeat(true);

    glutMainLoop();
    return 0;
}
