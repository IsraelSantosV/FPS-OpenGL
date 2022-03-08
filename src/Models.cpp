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
#include <typeinfo>
using namespace std;

enum TransformCategory {
    POSITION,
    ROTATION,
    SCALE
};

class WorldObject;
class Mesh;
typedef void TransformAction(Vector3, WorldObject*);
typedef void CustomDrawer(WorldObject*);

class Component {
private:
    WorldObject* m_Object;
public:
    explicit Component(WorldObject* wo){ m_Object = wo; }
    WorldObject* getObject() { return m_Object; }
    virtual void update(){ }
};

class Transform : public Component {
private:
    Vector3 m_Position;
    Vector3 m_Rotation;
    Vector3 m_Scale;

    vector<TransformAction*> m_OnChangePosition;
    vector<TransformAction*> m_OnChangeRotation;
    vector<TransformAction*> m_OnChangeScale;

    void triggerActionCategory(vector<TransformAction*> list, Vector3 reference){
        for(auto & i : list){
            (*i)(reference, getObject()); //Trigger Action
        }
    }

    void triggerActions(TransformCategory category){
        switch (category) {
            case POSITION:
                triggerActionCategory(m_OnChangePosition, m_Position);
                break;
            case ROTATION:
                triggerActionCategory(m_OnChangeRotation, m_Rotation);
                break;
            case SCALE:
                triggerActionCategory(m_OnChangeScale, m_Scale);
                break;
        }
    }
public:
    explicit Transform(WorldObject *wo) : Component(wo){
        setPosition(Vector3::ZERO());
        setRotation(Vector3::ZERO());
        setScale(Vector3::ONE());
    }

    void registerAction(TransformAction action, TransformCategory category){
        switch (category) {
            case POSITION:
                m_OnChangePosition.push_back(action);
                break;
            case ROTATION:
                m_OnChangeRotation.push_back(action);
                break;
            case SCALE:
                m_OnChangeScale.push_back(action);
                break;
        }
    }

    void setPosition(Vector3 position){
        Vector3 oldPosition = m_Position;
        m_Position.set(position.x, position.y, position.z);

        if(!m_Position.equals(oldPosition)){
            triggerActions(POSITION);
        }
    }

    void setRotation(Vector3 rotation){
        Vector3 oldRotation = m_Rotation;
        m_Rotation.set(rotation.x, rotation.y, rotation.z);

        if(!m_Rotation.equals(oldRotation)){
            triggerActions(ROTATION);
        }
    }

    void setScale(Vector3 scale){
        Vector3 oldScale = m_Scale;
        m_Scale.set(scale.x, scale.y, scale.z);

        if(!m_Scale.equals(oldScale)){
            triggerActions(SCALE);
        }
    }

    Vector3 getPosition() { return m_Position; }
    Vector3 getRotation() { return m_Rotation; }
    Vector3 getScale() { return m_Scale; }
};

class Section {
private:
    int m_ID;
    Vector3 m_StartPosition;
    Vector3 m_EndPosition;
    vector<WorldObject*> m_InsideObjects;
public:
    Section(int id, Vector3 startPos, Vector3 endPos) {
        m_ID = id;
        m_StartPosition.set(startPos.x, startPos.y, startPos.z);
        m_EndPosition.set(endPos.x, endPos.y, endPos.z);
    }

    Vector3 getStartPosition() { return m_StartPosition; }
    Vector3 getEndPosition() { return m_EndPosition; }
    int getID() const { return m_ID; }
    vector<WorldObject*> getInsideObjects() { return m_InsideObjects; }

    bool positionInsideSection(Vector3 position){
        return position >= m_StartPosition && position <= m_EndPosition;
    }

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
    Layer m_Layer;

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

    void validateCurrentSection(Section* targetSection){
        if(m_CurrentSection == nullptr || m_CurrentSection->getID() != targetSection->getID()){
            m_CurrentSection = targetSection;
        }
    }
public:
    explicit WorldObject(string name, WorldObject* parent = nullptr, Layer layer = DEFAULT){
        m_ID = "WO_" + Random::getNextID();
        m_Name = name;
        m_Layer = layer;

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

    Component* getComponent(const type_info& type){
        for(auto element : m_Components){
            if(typeid(*element).name() == type.name()){
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
        wo->validateCurrentSection(section);
    }

    static void removeObjectFromSection(WorldObject* wo, Section* section){
        if(!WorldObject::sectionContainsObject(wo, section)) return;
        int index = WorldObject::getObjectSectionIndex(wo);
        if(index == INVALID_INDEX) return;
        section->removeObject(index);
    }

    void updateComponents(){
        for(auto component : m_Components){
            component->update();
        }
    }

    string getName(){ return m_Name; }
    string getID() { return m_ID; }
    Transform* getTransform() { return m_Transform; }
    Layer getLayer() { return m_Layer; }
    bool isActive() { return m_Active; }
    void setActive(bool active) { m_Active = active; }
    void registerComponent(Component* component) { m_Components.push_back(component);}
    void setParent(WorldObject* parent) { m_Parent = parent; }
    void setMesh(Mesh *mesh) { m_Mesh = mesh; }
    void setLayer(Layer layer) { m_Layer = layer; }
    WorldObject* getParent() { return m_Parent; }
    Mesh* getMesh() { return m_Mesh; }
    Section* getSection() { return m_CurrentSection; }
};

class Collider : public Component {
private:
    Vector3 m_Size;
    Vector3 m_Offset;
public:
    explicit Collider(WorldObject* wo, Vector3 size, Vector3 offset) : Component(wo){
        m_Size.set(size);
        m_Offset.set(offset);
    }

    Vector3 getPosition(){
        Vector3 woPosition = getObject()->getTransform()->getPosition();
        return Vector3(woPosition.x, woPosition.y, woPosition.z) + m_Offset;
    }

    void drawDebug(){
        Transform* t = getObject()->getTransform();
        glPushMatrix();
        glScalef(m_Size.x, m_Size.y, m_Size.z);
        glRotatef(0, t->getRotation().x, t->getRotation().y, t->getRotation().z);
        glTranslatef(getPosition().x, 0, getPosition().z);
        glutWireCube(DEFAULT_SIZE);
        glPopMatrix();
    }

    Vector3 getSize() { return m_Size; }
    Vector3 getOffset() { return m_Offset; }
};

class Mesh : public Component {
private:
    Vector3 m_Color = Vector3::ONE();
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
    explicit Mesh(WorldObject* obj) : Component(obj){ }
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

class CustomMesh : public Mesh {
private:
    CustomDrawer* m_Drawer;
public:
    CustomMesh(WorldObject* wo, CustomDrawer drawerAction) : Mesh(wo){
        m_Drawer = drawerAction;
    }

    void drawProperties() override {
        m_Drawer(getObject());
    }
};

#endif //FP_OPENGL_MODELS_CPP