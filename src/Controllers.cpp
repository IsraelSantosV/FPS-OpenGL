//
// Created by Israel Santos Vieira (Computer scientist) - All rights reserved
//

#ifndef FP_OPENGL_CONTROLLERS_CPP
#define FP_OPENGL_CONTROLLERS_CPP

#define TO_RADIANS 3.14/180.0
#define GROUND_SCALE 50
#define GROUND_HEIGHT 5
#include <math.h>
#include <GL/glut.h>
#include <vector>
#include "Tools.cpp"
#include "InputManager.cpp"
#include "Models.cpp"
#include "Debug.cpp"
#include "Grid.cpp"
#include "Time.cpp"

struct DebugMesh {
    CustomMesh* Mesh;
    float Duration;
    float CurrentTime;
};

class Scenario {
private:
    vector<WorldObject*> m_RuntimeObjects;
    vector<DebugMesh*> m_DebugObjects;
    static Scenario* m_Instance;
    Grid* m_Grid;

    Scenario(){
        m_Grid = new Grid(GROUND_SCALE / 2, -GROUND_HEIGHT,
                          50, Vector3(-GROUND_SCALE, 0, -GROUND_SCALE));

        //Create a ground to test scenario
        WorldObject* ground = instantiate("Ground");
        CustomMesh* customMesh = new CustomMesh(ground, [](WorldObject* wo){
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
                    glTexCoord2f(0.0,0.0);  glVertex3f(-GROUND_SCALE,-GROUND_HEIGHT,-GROUND_SCALE);
                    glTexCoord2f(GROUND_SCALE/2,0.0);  glVertex3f(GROUND_SCALE,-GROUND_HEIGHT,-GROUND_SCALE);
                    glTexCoord2f(GROUND_SCALE/2,GROUND_SCALE/2);  glVertex3f(GROUND_SCALE,-GROUND_HEIGHT,GROUND_SCALE);
                    glTexCoord2f(0.0,GROUND_SCALE/2);  glVertex3f(-GROUND_SCALE,-GROUND_HEIGHT,GROUND_SCALE);
                glEnd();
            glDisable(GL_TEXTURE_2D);
        });

        ground->setMesh(customMesh);
        ground->setLayer(GROUND);
        Debug::log("[3/5] Starting rendering scenario...");
    }

    void registerObject(WorldObject* obj){
        if(obj == nullptr) return;
        m_RuntimeObjects.push_back(obj);

        Vector3 objPosition = obj->getTransform()->getPosition();
        WorldObject::insertObjectIntoSection(obj, getGrid()->getSection(objPosition));
    }
public:
    static Scenario* getInstance(){
        if(m_Instance == nullptr){
            m_Instance = new Scenario();
        }

        return m_Instance;
    }

    void initialize(){ }

    void drawScenario(){
        //Draw Basics
        if(DRAW_DEBUG) {
            getGrid()->drawGrid();
        }

        //Draw WorldObjects
        for(auto obj : m_RuntimeObjects){
            if(obj == nullptr || !obj->isActive()) continue;
            //Update object components
            obj->updateComponents();

            //Update object mesh
            if(obj->getMesh() == nullptr) continue;
            obj->getMesh()->draw();
        }

        //Draw debug gizmos
        for(auto i = 0; i < m_DebugObjects.size(); ++i){
            auto debug = m_DebugObjects[i];
            if(debug == nullptr || debug->Mesh == nullptr) continue;
            debug->CurrentTime += Time::deltaTime();

            if(debug->CurrentTime >= debug->Duration){
                //m_DebugObjects.erase(m_DebugObjects.begin() + i);
            }
            else {
                if(debug->Mesh != nullptr) {
                    debug->Mesh->draw();
                }
            }
        }
    }

    WorldObject* instantiate(string name, WorldObject* parent = nullptr){
        WorldObject* newObject = new WorldObject(name, parent);
        registerObject(newObject);
        return newObject;
    }

    void drawDebug(CustomMesh* debugMesh, float duration){
        DebugMesh* debug = new DebugMesh();
        debug->Mesh = debugMesh;
        debug->Duration = duration;
        debug->CurrentTime = 0;
        m_DebugObjects.push_back(debug);
    }

    Grid* getGrid() { return m_Grid; }
};

//STRONG DEPENDENCY WITH CONTROLLER
class Movable : public ObjectComponent {
private:
    Transform* m_Transform;
public:
    explicit Movable(WorldObject *wo) : ObjectComponent(wo){
        m_Transform = wo->getTransform();

        m_Transform->registerAction([](Vector3 currentPosition, WorldObject* myObject){
            Scenario* instance = Scenario::getInstance();
            Section* currentSection = instance->getGrid()->getSection(currentPosition);

            if(currentSection->getID() != myObject->getSection()->getID()){
                WorldObject::removeObjectFromSection(myObject, myObject->getSection());
                WorldObject::insertObjectIntoSection(myObject, currentSection);
            }
        }, POSITION);
    }
};

class Physics {
public:
    static vector<WorldObject*> raycast(Vector3 origin, Vector3 forward, float raySize, int precision,
                                        float minDistance, LayerMask* mask){

        float sectionedRaySize = raySize / (float)precision;
        Grid* grid = Scenario::getInstance()->getGrid();

        vector<WorldObject*> hitObjects;
        for(int i = 0; i < precision; ++i){
            Vector3 finalPoint = Vector3(origin.x * sectionedRaySize * i * forward.x,
                                         origin.y * sectionedRaySize * i * forward.y,
                                         origin.z * sectionedRaySize * i * forward.z);

            Section* raySection = grid->getSection(finalPoint);
            if(raySection == nullptr) continue;

            vector<WorldObject*> sectionObjects = raySection->getInsideObjects();
            for(auto obj : sectionObjects){
                if(!Layers::layerInLayerMask(obj->getLayer(), mask)) continue;
                Vector3 objPosition = obj->getTransform()->getPosition();
                if(Physics::distance(objPosition, finalPoint) > minDistance) continue;
                hitObjects.push_back(obj);
            }
        }

        return hitObjects;
    }

    static float distance(Vector3 a, Vector3 b){
        return sqrt(pow((b.x - a.x), 2) + pow((b.y - a.y), 2) + pow((b.z - a.z), 2));
    }
};

class Camera {
private:
    int m_ScreenWidth;
    int m_ScreenHeight;
    Vector3 m_VerticalLimit;
    float m_Speed;
    float m_Sensibility;
    bool m_CursorLocked;
    WorldObject* m_WorldObject;

    static Camera* m_Instance;
    Camera(){
        m_Speed = 5;
        m_Sensibility = 30;
        m_CursorLocked = true;
        m_ScreenWidth = 800;
        m_ScreenHeight = 600;

        m_WorldObject = Scenario::getInstance()->instantiate("Controller");
        m_WorldObject->setLayer(PLAYER);
        m_WorldObject->registerComponent(new Movable(m_WorldObject));
        Debug::log("[4/5] Creating camera...");
    }
public:
    static Camera* getInstance(){
        if(m_Instance == nullptr){
            m_Instance = new Camera();
        }

        return m_Instance;
    }

    WorldObject* getObject() { return m_WorldObject; }

    void setScreenSize(int width, int height){
        m_ScreenWidth = width;
        m_ScreenHeight = height;
    }

    void initialize(float speed, float smoothCamera){
        m_Speed = speed;
        m_Sensibility = smoothCamera;
    }

    void receiveMousePosition(int x, int y){
        float sensibility = getSensibility();
        Vector3 currentRot = getRotation();
        float currentYaw = currentRot.x;
        float currentPitch = currentRot.y;

        float targetYaw = isFreeze() ? currentYaw : currentYaw + (float)x/sensibility;
        float targetPitch = isFreeze() ? currentPitch : currentPitch + (float)y/sensibility;
        setRotation(Vector3(targetYaw, targetPitch));
    }

    void updateMovement(){
        InputKey* forward = InputManager::getInstance()->getKey("Vertical", true);
        InputKey* backward = InputManager::getInstance()->getKey("Vertical", false);
        InputKey* right = InputManager::getInstance()->getKey("Horizontal", true);
        InputKey* left = InputManager::getInstance()->getKey("Horizontal", false);

        float yaw = getRotation().x;
        float pitch = getRotation().y;

        if(forward != nullptr && forward->isPressed()){
            setMovement(Vector3(
                    getPosition().x + cos((yaw+90)*TO_RADIANS)/getSpeed(), 0,
                    getPosition().z - sin((yaw+90)*TO_RADIANS)/getSpeed()
            ));
        }
        if(backward != nullptr && backward->isPressed()){
            setMovement(Vector3(
                    getPosition().x + cos((yaw+90+180)*TO_RADIANS)/getSpeed(), 0,
                    getPosition().z - sin((yaw+90+180)*TO_RADIANS)/getSpeed()
            ));
        }
        if(right != nullptr && right->isPressed()){
            setMovement(Vector3(
                    getPosition().x + cos((yaw+90-90)*TO_RADIANS)/getSpeed(), 0,
                    getPosition().z - sin((yaw+90-90)*TO_RADIANS)/getSpeed()
            ));
        }
        if(left != nullptr && left->isPressed()){
            setMovement(Vector3(
                    getPosition().x + cos((yaw+90+90)*TO_RADIANS)/getSpeed(), 0,
                    getPosition().z - sin((yaw+90+90)*TO_RADIANS)/getSpeed()
            ));
        }

        glRotatef(-pitch,1.0,0.0,0.0); // Along X axis
        glRotatef(-yaw,0.0,1.0,0.0);    //Along Y axis
        glTranslatef(-getPosition().x,0.0,-getPosition().z);
    }

    void setVerticalLimit(Vector3 limit){
        m_VerticalLimit.set(limit.x, limit.y, limit.z);
    }

    void setMovement(Vector3 position){
        getObject()->getTransform()->setPosition(position);
    }

    void setRotation(Vector3 rotation){
        float clampedPitch = rotation.y;
        if(clampedPitch >= m_VerticalLimit.x){
            clampedPitch = m_VerticalLimit.x;
        }
        if(clampedPitch <= -m_VerticalLimit.y){
            clampedPitch = -m_VerticalLimit.y;
        }

        getObject()->getTransform()->setRotation(Vector3(rotation.x, clampedPitch, rotation.z));
    }

    Vector3 getPosition() { return getObject()->getTransform()->getPosition(); }
    Vector3 getRotation() { return getObject()->getTransform()->getRotation(); }
    float getSpeed(){ return m_Speed; }
    float getSensibility() { return m_Sensibility; }
    bool cursorIsLocked() { return m_CursorLocked; }
    bool isFreeze() { return !cursorIsLocked(); }

    void setCursorLockState(bool locked){
        m_CursorLocked = locked;
        if(m_CursorLocked){
            glutWarpPointer(m_ScreenWidth/2,m_ScreenHeight/2);
            glutSetCursor(GLUT_CURSOR_NONE);
        }
        else {
            glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
        }
    }

    void registerActionTriggers(){
        InputKey* escapeKey = InputManager::getInstance()->getKey(ESCAPE);
        if (escapeKey != nullptr) {
            escapeKey->registerAction([](){
                Camera* currentCamera = Camera::getInstance();
                currentCamera->setCursorLockState(!currentCamera->cursorIsLocked());
            }, ONE_TIME);
        }

        InputKey* submitKey = InputManager::getInstance()->getKey(SPACE);
        if(submitKey != nullptr){
            submitKey->registerAction([](){
                Camera* currentCamera = Camera::getInstance();
                cout << currentCamera->getPosition().toString() << endl;

                if(currentCamera->getObject()->getSection() != nullptr){
                    cout << "CurrentSection: " << currentCamera->getObject()->getSection()->getID() << endl;
                }
                else{
                    cout << "CurrentSection: None";
                }

            }, ONE_TIME);
        }

        InputKey* interactKey = InputManager::getInstance()->getKey("Interact", true);
        if(interactKey != nullptr){
            interactKey->registerAction([](){
                Camera* camera = Camera::getInstance();

                Layer layers[] = { DEFAULT, OBSTACLE };
                vector<WorldObject*> hitResult = Physics::raycast(camera->getPosition(),
                                                                  camera->getRotation(), 5, 30,
                                                                  0.5, new LayerMask(layers));

                Scenario::getInstance()->drawDebug(new CustomMesh(new WorldObject("Debug"), [](WorldObject* obj){
                    Camera* camera = Camera::getInstance();
                    Vector3 cameraPos = camera->getPosition();
                    Vector3 targetPoint = Vector3(cameraPos.x * 5, cameraPos.y * 5, cameraPos.z * 5);

                    glPushMatrix();
                        glBegin(GL_LINE);
                            glVertex3f(cameraPos.x, cameraPos.y, cameraPos.z);
                            glVertex3f(targetPoint.x, targetPoint.y, targetPoint.z);
                        glEnd();
                    glPopMatrix();
                }), 5.0);

                for(auto hit : hitResult){
                    Debug::log(hit->getName());
                }
            }, ONE_TIME);
        }
    }
};

#endif //FP_OPENGL_CONTROLLERS_CPP