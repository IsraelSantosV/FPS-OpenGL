#include <GL/glut.h>
#include "Controllers.cpp"
#include "Debug.cpp"
#include "Time.cpp"
#define FPS 60.0

InputManager* InputManager::m_Instance = nullptr;
Scenario* Scenario::m_Instance = nullptr;
Camera* Camera::m_Instance = nullptr;
LayerMatrix* LayerMatrix::m_Instance = nullptr;

int Random::RANDOM_ID = 0;
float Time::m_DeltaTime = 0;
float Time::m_GameTime = 0;

//Width and height of the window (Aspect ratio 16:9)
const int sceneScale = 100;
const int width = 16*sceneScale;
const int height = 9*sceneScale;

void display();
void reshape(int w,int h);
void createScenarioObjects();
void timer(int);
void passive_motion(int,int);
void keyboard(unsigned char key,int x,int y);
void keyboard_up(unsigned char key,int x,int y);

void init(){
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    Debug::log("[2/5] Loading singletons and OpenGL extensions...");

    LayerMatrix::getInstance()->initialize();
    LayerMatrix::getInstance()->addToEverything(DEFAULT);
    LayerMatrix::getInstance()->addToEverything(OBSTACLE);
    LayerMatrix::getInstance()->addToEverything(PLAYER);

    LayerMatrix::getInstance()->clearLayer(NO_COLLISION);
    LayerMatrix::getInstance()->clearLayer(GROUND);

    Scenario::getInstance()->initialize();
    Camera::getInstance()->initialize(5, 30);
    Camera::getInstance()->setScreenSize(width, height);
    Camera::getInstance()->setVerticalLimit(Vector3(70, 60, 0));
    Camera::getInstance()->setCursorLockState(true);
    Camera::getInstance()->registerActionTriggers();

    createScenarioObjects();
}

void setupInputs(){
    InputManager::getInstance()->addKey('w', "Vertical", true);
    InputManager::getInstance()->addKey('s', "Vertical", false);
    InputManager::getInstance()->addKey('a', "Horizontal", false);
    InputManager::getInstance()->addKey('d', "Horizontal", true);
    InputManager::getInstance()->addKey('f', "Interact", true);
    InputManager::getInstance()->addKey(ESCAPE, "Escape", true);
    InputManager::getInstance()->addKey(SPACE, "Submit", true);
}

void createScenarioObjects(){
    Debug::log("[5/5] Rendering scenario objects...");
    { //Create a cube
        WorldObject* cube = Scenario::getInstance()->instantiate("Cube", Vector3(-5, 0, 5), Vector3::ZERO(), true);
        cube->setLayer(OBSTACLE);
        cube->setMesh(new CubeMesh(cube, false));
        cube->getTransform()->setScale(Vector3(2,3,5));
        cube->getMesh()->setColor(Vector3(0,0,1));
        cube->registerComponent(new Collider(cube, cube->getTransform()->getScale(), Vector3::ZERO()));

        Debug::log(cube->getTransform()->getPosition().toString());
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    Camera::getInstance()->updateMovement();
    if(DRAW_DEBUG) { Camera::getInstance()->drawCameraDebug(); }
    Scenario::getInstance()->drawScenario();
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

    Time::refreshTime((1000/FPS) / 1000);
    glutTimerFunc(1000/FPS,timer,0);
    Scenario::getInstance()->updateRuntimeObjects();
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
    glutCreateWindow("VoxEngine");

    setupInputs();
    glutReshapeFunc(reshape);

    init();
    glutDisplayFunc(display);
    glutTimerFunc(0,timer,0);
    glutPassiveMotionFunc(passive_motion);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboard_up);
    glutIgnoreKeyRepeat(true);

    glutMainLoop();
    return 0;
}
