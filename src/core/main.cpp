#include <GL/glut.h>
#include "controllers/headers/camera.h"

#define FPS 60

//width and height of the window ( Aspect ratio 16:9 )
const int width = 16*50;
const int height = 9*50;
camera fpsCamera(width, height);
inputManager myInputManager;

void display();
void reshape(int w,int h);
void timer(int);
void passive_motion(int,int);
void keyboard(unsigned char key,int x,int y);
void keyboard_up(unsigned char key,int x,int y);

void init(){
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    fpsCamera.setCursorLockState(true);
}

void setupInputs(){
    myInputManager.addKey('w', "Vertical", true);
    myInputManager.addKey('s', "Vertical", false);
    myInputManager.addKey('a', "Horizontal", false);
    myInputManager.addKey('d', "Horizontal", true);
}

void draw(){
    glEnable(GL_TEXTURE_2D);
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
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    fpsCamera.updateMovement(myInputManager);
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

    if(fpsCamera.cursorIsLocked()){
        glutWarpPointer(width/2,height/2);
    }

    glutTimerFunc(1000/FPS,timer,0);
}

void passive_motion(int x,int y){
    int dev_x,dev_y;
    const float sensibility = 10;
    dev_x = (width/2)-x;
    dev_y = (height/2)-y;

    vector3 currentRot = fpsCamera.getRotation();
    float currentYaw = currentRot.X();
    float currentPitch = currentRot.Y();

    float targetYaw = currentYaw + (float)dev_x/sensibility;
    float targetPitch = currentPitch + (float)dev_y/sensibility;
    fpsCamera.setRotation(vector3(targetYaw, targetPitch));
}

void keyboard(unsigned char key,int x,int y){
    myInputManager.updateKeys(key, PRESSED);
    /*switch(key){
        case 'W':
        case 'w':
            motion.Forward = true;
            break;
        case 'A':
        case 'a':
            motion.Left = true;
            break;
        case 'S':
        case 's':
            motion.Backward = true;
            break;
        case 'D':
        case 'd':
            motion.Right = true;
            break;
    }*/
}

void keyboard_up(unsigned char key,int x,int y){
    myInputManager.updateKeys(key, RELEASED);
    /*switch(key){
        case 'W':
        case 'w':
            motion.Forward = false;
            break;
        case 'A':
        case 'a':
            motion.Left = false;
            break;
        case 'S':
        case 's':
            motion.Backward = false;
            break;
        case 'D':
        case 'd':
            motion.Right = false;
            break;
    }*/
}

int main(int argc,char**argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("3D Simulation");

    init();
    setupInputs();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0,timer,0);
    glutPassiveMotionFunc(passive_motion);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboard_up);

    glutMainLoop();
    return 0;
}
