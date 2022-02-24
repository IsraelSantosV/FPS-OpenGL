//
// Created by Israel Santos Vieira (Computer scientist) - All rights reserved
//

#ifndef FP_OPENGL_MODELS_CPP
#define FP_OPENGL_MODELS_CPP
#define DEFAULT_SIZE 1
#define INVALID_INDEX -999

#include <iostream>
#include <vector>
#include <GL/glut.h>
#include "Tools.cpp"
using namespace std;

class WorldObject;
class Mesh;

class Component {
private:
    string m_Name;
    WorldObject* m_Object;
public:
    explicit Component(WorldObject* wo){ m_Object = wo; }
    string getName() { return m_Name; }
    WorldObject* getObject() { return m_Object; }
};

class Transform : public Component {
private:
    Vector3 m_Position;
    Vector3 m_Rotation;
    Vector3 m_Scale;
public:
    explicit Transform(WorldObject *wo) : Component(wo){
        setPosition(Vector3());
        setRotation(Vector3());
        setScale(Vector3(1,1,1));
    }

    void setPosition(Vector3 position){
        m_Position.set(position.x, position.y, position.z);
    }

    void setRotation(Vector3 rotation){
        m_Rotation.set(rotation.x, rotation.y, rotation.z);
    }

    void setScale(Vector3 scale){
        m_Scale.set(scale.x, scale.y, scale.z);
    }

    Vector3 getPosition() { return m_Position; }
    Vector3 getRotation() { return m_Rotation; }
    Vector3 getScale() { return m_Scale; }
};

class Section {
private:
    int m_ID;
    Vector3 m_Position;
    vector<WorldObject*> m_InsideObjects;
public:
    Section(int id, Vector3 position) {
        m_ID = id;
        m_Position.set(position.x, position.y, position.z);
    }

    Vector3 getPosition() { return m_Position; }
    int getID() { return m_ID; }
    vector<WorldObject*> getInsideObjects() { return m_InsideObjects; }

    void insertObject(WorldObject* wo){
        if(wo == nullptr) return;
        m_InsideObjects.push_back(wo);
    }

    void removeObject(int index){
        if(index < 0 || index >= m_InsideObjects.size()) return;
        m_InsideObjects.erase(m_InsideObjects.begin() + index);
    }
};

class WorldObject {
private:
    string m_Name;
    string m_ID;
    Transform* m_Transform;
    bool m_Active;
    vector<Component*> m_Components;
    WorldObject* m_Parent;
    Mesh* m_Mesh;
    Section* m_CurrentSection;

    static int getObjectSectionIndex(WorldObject* wo){
        if(wo->m_CurrentSection == nullptr) return INVALID_INDEX;
        vector<WorldObject*> allObjects = wo->m_CurrentSection->getInsideObjects();

        for (int i = 0; i < allObjects.size(); i++){
            if(allObjects[i] == nullptr) continue;
            if (allObjects[i]->getID() == wo->getID()){
                return i;
            }
        }

        return INVALID_INDEX;
    }
public:
    explicit WorldObject(string name, WorldObject* parent = nullptr){
        m_ID = "WO_" + Random::getNextID();
        m_Name = name;
        m_Active = true;
        m_Mesh = nullptr;
        m_Parent = nullptr;
        m_CurrentSection = nullptr;
        setParent(parent);
        m_Transform = new Transform(this);
        registerComponent(m_Transform);
    }

    ~WorldObject(){
        for(auto & m_Component : m_Components){
            delete m_Component;
        }
    }

    Component* getComponent(const string& name){
        for(auto element : m_Components){
            if(element->getName() == name){
                return element;
            }
        }

        return nullptr;
    }

    static bool sectionContainsObject(WorldObject* wo, Section* section){
        if(wo == nullptr || section == nullptr) return false;
        for(auto object : section->getInsideObjects()){
            if(object->getID() == wo->getID()){
                return true;
            }
        }

        return false;
    }

    static void insertObjectIntoSection(WorldObject* wo, Section* section){
        if(wo == nullptr || section == nullptr || WorldObject::sectionContainsObject(wo, section)) return;
        section->insertObject(wo);
    }

    static void removeObjectFromSection(WorldObject* wo, Section* section){
        if(!WorldObject::sectionContainsObject(wo, section)) return;
        int index = WorldObject::getObjectSectionIndex(wo);
        if(index == INVALID_INDEX) return;
        section->removeObject(index);
    }

    string getName(){ return m_Name; }
    string getID() { return m_ID; }
    Transform* getTransform() { return m_Transform; }
    bool isActive() { return m_Active; }
    void setActive(bool active) { m_Active = active; }
    void registerComponent(Component* component) { m_Components.push_back(component);}
    void setParent(WorldObject* parent) { m_Parent = parent; }
    void setMesh(Mesh *mesh) { m_Mesh = mesh; }
    WorldObject* getParent() { return m_Parent; }
    Mesh* getMesh() { return m_Mesh; }
    Section* getSection() { return m_CurrentSection; }
};

class ObjectComponent : public Component {
public:
    explicit ObjectComponent(WorldObject* wo) : Component(wo) {
        if(wo != nullptr){
            wo->registerComponent(this);
        }
    }
};

class Mesh : public ObjectComponent {
private:
    Vector3 m_Color = Vector3(1,1,1);
    float m_Alpha = 1;

    void internal_drawing(){
        glPushMatrix();
        Transform* t = getObject()->getTransform();
        Vector3 position = t->getPosition();
        Vector3 rotation = t->getRotation();
        Vector3 scale = t->getScale();

        glColor4f(m_Color.x, m_Color.y, m_Color.z, m_Alpha);
        glScalef(scale.x, scale.y, scale.z);
        glRotatef(0, rotation.x, rotation.y, rotation.z);
        glTranslatef(position.x, position.y, position.z);
        drawProperties();
        glPopMatrix();

    }
protected:
    virtual void drawProperties() { }
public:
    explicit Mesh(WorldObject* obj) : ObjectComponent(obj){ }
    void draw() { internal_drawing(); }

    void setColor(Vector3 color, float alpha = 1){
        m_Color.x = color.x;
        m_Color.y = color.y;
        m_Color.z = color.z;
        m_Alpha = alpha;
    }
};

class CubeMesh : public Mesh {
public:
    CubeMesh(WorldObject* wo, bool wired) : Mesh(wo){
        m_Wired = wired;
    }
protected:
    bool m_Wired;

    void drawProperties() override {
        if(m_Wired){ glutWireCube(DEFAULT_SIZE); }
        else { glutSolidCube(DEFAULT_SIZE); }
    }
};

#endif //FP_OPENGL_MODELS_CPP