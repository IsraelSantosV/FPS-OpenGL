//
// Created by Israel Santos Vieira (Computer scientist) - All rights reserved
//

#ifndef FP_OPENGL_CONTROLLERS_CPP
#define FP_OPENGL_CONTROLLERS_CPP

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
        WorldObject* ground = instantiate("Ground", Vector3(), Vector3(), false);
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

            if(DRAW_DEBUG) {
                auto *i = dynamic_cast<Collider *>(obj->getComponent(typeid(Collider)));
                if (i != nullptr){
                    i->drawDebug();
                }
            }

            //Update object mesh
            if(obj->getMesh() == nullptr) continue;
            obj->getMesh()->draw();
        }

        //Draw debug gizmos
        /*for(auto i = 0; i < m_DebugObjects.size(); ++i){
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
        }*/
    }

    //Update runtime objects for each frame (FPS) - DeltaTime
    void updateRuntimeObjects(){
        for(auto obj : m_RuntimeObjects) {
            if(obj == nullptr || !obj->isActive()) continue;
            //Update object components
            obj->updateComponents();
        }
    }

    WorldObject* instantiate(string name, WorldObject* parent, bool registerMoveAction){
        WorldObject* wo = instantiate(name, Vector3(), Vector3(), registerMoveAction);
        wo->setParent(parent);
        return wo;
    }

    WorldObject* instantiate(string name, Vector3 position, bool registerMoveAction){
        return instantiate(name, position, Vector3(), registerMoveAction);
    }

    WorldObject* instantiate(string name, Vector3 position, Vector3 rotation, bool registerMoveAction){
        WorldObject* newObject = new WorldObject(name, nullptr);
        newObject->getTransform()->setPosition(position);
        newObject->getTransform()->setRotation(rotation);

        if(registerMoveAction) {
            newObject->getTransform()->registerAction([](Vector3 position, WorldObject *wo) {
                Grid *currentGrid = Scenario::getInstance()->getGrid();
                WorldObject::insertObjectIntoSection(wo, currentGrid->getSection(position));
            }, POSITION);
        }

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
class SectionMovable : public Component {
private:
    Transform* m_Transform;
public:
    explicit SectionMovable(WorldObject *wo) : Component(wo){
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

class FieldOfView {
private:
    float m_ViewAngle;
    Vector3 m_ForwardVector;
    Vector3 m_DebugColor;
    WorldObject* m_Object;
public:
    FieldOfView(WorldObject* wo, float viewAngle, Vector3 forwardVector){
        m_Object = wo;
        m_ViewAngle = viewAngle;
        m_ForwardVector = forwardVector;
        m_DebugColor = Vector3(0, 1, 0);
    }

    vector<WorldObject*> getObjectsInsideView(Vector3 directionToTarget, vector<WorldObject*>& objects){
        vector<WorldObject*> result;
        for(auto obj : objects){
            if(Vector3::angle(getForwardVector(), directionToTarget) < getViewAngle() / 2){
                result.push_back(obj);
            }
        }

        return result;
    }

    void drawDebug(){
        glPushMatrix();
            glColor4f(m_DebugColor.x, m_DebugColor.y, m_DebugColor.z, 0.8);

            Transform* transform = m_Object->getTransform();
            Vector3 position = transform->getPosition();

            Vector3 viewAngleA = (Vector3::directionFromAngle(-getViewAngle() / 2) * getViewAngle()) + position;
            Vector3 viewAngleB = (Vector3::directionFromAngle(getViewAngle() / 2) * getViewAngle()) + position;

            //Draw first line
            glVertex3f(position.x, position.y, position.z);
            glVertex3f(viewAngleA.x, viewAngleA.y, viewAngleA.z);

            //Draw second line
            glVertex3f(position.x, position.y, position.z);
            glVertex3f(viewAngleB.x, viewAngleB.y, viewAngleB.z);
        glPopMatrix();
    }

    float getViewAngle(){ return m_ViewAngle; }
    Vector3 getForwardVector() { return m_ForwardVector; }
    void setViewAngle(float angle) { m_ViewAngle = angle; }
    void setForwardVector(Vector3 forwardVector) { m_ForwardVector.set(forwardVector); }
};

class Physics {
private:
    static vector<WorldObject*> getSectionRayObjects(Section* currentSection, Vector3 currentRayPoint){
        vector<WorldObject*> insideRadiusObjects;
        Grid* grid = Scenario::getInstance()->getGrid();

        for(auto obj : currentSection->getInsideObjects()){
            insideRadiusObjects.push_back(obj);
        }

        //TODO -> THINK: Use the remainder of the division between the radius size and
        // the size of a section to define how many times the radius should be
        // partitioned to perform section calculations

        if(!currentSection->positionInsideSection(currentRayPoint)){
            //When ray size is bigger than section size -> add all elements from target section
            //TODO -> Insert loop to handle a ray that is greater than a section
            Section* incrementSection = grid->getSection(currentRayPoint);
            if(incrementSection != nullptr && incrementSection->getID() != currentSection->getID()) {
                for (auto obj: incrementSection->getInsideObjects()) {
                    insideRadiusObjects.push_back(obj);
                }
            }
        }

        return insideRadiusObjects;
    }
public:
    static bool detectCollision(WorldObject* target, Vector3 nextStep, double minDistance) {
        if (target == nullptr || nextStep.equals(Vector3(0, 0, 0))) return false;

        auto* targetCollider = dynamic_cast<Collider *>(target->getComponent(typeid(Collider)));
        if(targetCollider == nullptr) return false;

        Section* targetSection = target->getSection();
        if(targetSection == nullptr) return false;

        vector<WorldObject*> sectionObjects = targetSection->getInsideObjects();
        LayerMatrix* physicsMatrix = LayerMatrix::getInstance();

        Vector3 currentPosition = targetCollider->getPosition() + nextStep;

        for(auto object : sectionObjects){
            if(object == nullptr || object->getID() == target->getID()) continue;
            if(!physicsMatrix->canApplyPhysics(target->getLayer(), object->getLayer())){
                continue;
            }

            //Get object collider to get position offset
            auto* collider = dynamic_cast<Collider *>(object->getComponent(typeid(Collider)));
            if(collider == nullptr) continue;

            double targetDistance = Vector3::distance(currentPosition, collider->getPosition());
            Debug::log("Trying collision with (" + object->getName() + ") | Distance: " + to_string(targetDistance));

            if(targetDistance < minDistance){
                return true;
            }
        }

        return false;
    }

    static vector<WorldObject*> raycast(Vector3 origin, FieldOfView* fov, float raySize, LayerMask* mask){
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        //Initialize values
        Grid* myGrid = Scenario::getInstance()->getGrid();
        vector<WorldObject*> hitObjects;

        //Get all objects in field of view of the origin
        Section* currentSection = myGrid->getSection(origin);
        Vector3 targetRayPoint = origin * raySize;
        Vector3 rayDirection = Vector3::normalize((targetRayPoint - origin));

        vector<WorldObject*> insideSectionObjects = getSectionRayObjects(currentSection, targetRayPoint);
        vector<WorldObject*> objectsInsideFov = fov->getObjectsInsideView(rayDirection, insideSectionObjects);

        for(auto obj : objectsInsideFov){
            float distToTarget = Vector3::distance(origin, targetRayPoint);
            if(distToTarget <= 0){
                hitObjects.push_back(obj);
            }
        }

        glMatrixMode(GL_MODELVIEW);
        return hitObjects;
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
    FieldOfView* m_FieldOfView;
    bool m_DetectCollisions;

    static Camera* m_Instance;
    Camera(){
        m_Speed = 5;
        m_Sensibility = 30;
        m_CursorLocked = true;
        m_ScreenWidth = 800;
        m_ScreenHeight = 600;
        m_DetectCollisions = true;

        m_WorldObject = Scenario::getInstance()->instantiate("Controller", Vector3::ZERO(), Vector3::ZERO(), false);
        m_WorldObject->setLayer(PLAYER);
        m_WorldObject->registerComponent(new SectionMovable(m_WorldObject));
        m_FieldOfView = new FieldOfView(m_WorldObject, 90, Vector3::FORWARD());
        m_WorldObject->registerComponent(new SectionMovable(m_WorldObject));

        if(m_DetectCollisions){
            m_WorldObject->registerComponent(
                    new Collider(m_WorldObject, Vector3(1,2,1), Vector3()));
        }

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

    void drawCameraDebug(){
        if(getFieldOfView() != nullptr){
            getFieldOfView()->drawDebug();
        }
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
        Vector3 targetMovement = Vector3(position.x, GROUND_HEIGHT, position.z);
        if(m_DetectCollisions){
            if(Physics::detectCollision(m_WorldObject, targetMovement, 1)){
                return;
            }
        }

        getObject()->getTransform()->setPosition(targetMovement);
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
    FieldOfView* getFieldOfView() { return m_FieldOfView; }

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
                                                                  camera->getFieldOfView(), 5, new LayerMask(layers));

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