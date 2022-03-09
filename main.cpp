#include "GL/glut.h"

float lastX = ScreenWidth / 2.0f;
float lastY = ScreenHeight / 2.0f;
bool firstMouse = true;

void idle(){
    if(!camera->onGround && !camera->isFalling){
        camera->rise();
    }
    else if(!camera->onGround){
        camera->fall();
    }

    if(camMove.forward || camMove.backward || camMove.left || camMove.right){
        camera->processKeyboard(deltaTime);
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    ScreenWidth = glutGet(GLUT_SCREEN_WIDTH) / 1.2;
    ScreenHeight = glutGet(GLUT_SCREEN_HEIGHT);

    glutInitWindowSize(ScreenWidth, ScreenHeight);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL Camera");
    glutFullScreen();

    glutMainLoop();
    return(EXIT_SUCCESS);
}
