//
// Created by Israel Santos Vieira (Computer scientist) - All rights reserved
//

#ifndef FP_OPENGL_GRID_CPP
#define FP_OPENGL_GRID_CPP
#include "Models.cpp"
#include "math.h"
using namespace std;

class Grid {
private:
    int m_GridSize;
    int m_LateralSize;
    float m_YLevel;
    int m_SectionSize;
    int m_TotalSections;
    vector<Section*> m_Sections;
public:
    Grid(int gridSize, float yLevel, int sectionSize, Vector3 startPoint){
        m_GridSize = gridSize;
        m_YLevel = yLevel;
        m_SectionSize = sectionSize;

        m_TotalSections = (m_GridSize * m_GridSize) / sectionSize;
        m_LateralSize = sqrt(m_TotalSections);

        float startX = 0;
        float startZ = 0;
        float finalX = m_SectionSize;
        float finalZ = m_SectionSize;

        int currentID = 0;
        int iterator = 1;

        for(int x = 0; x < m_TotalSections; x++){
            Vector3 startPosition = Vector3(startX + startPoint.x, yLevel, startZ + startPoint.z);
            Vector3 finalPosition = Vector3(finalX + startPoint.x, yLevel, finalZ + startPoint.z);
            Section* section = new Section(currentID, startPosition, finalPosition);
            m_Sections.push_back(section);

            currentID++;
            iterator++;

            //Update coordinate values
            finalX += m_SectionSize;
            startX += m_SectionSize;

            if(iterator > m_LateralSize){
                finalX = m_SectionSize;
                startX = 0;

                finalZ += m_SectionSize;
                startZ += m_SectionSize;
                iterator = 1;
            }
        }
    }

    ~Grid(){
        for(int i = 0; i < m_TotalSections; i++){
            delete m_Sections[i];
        }
    }

    float getYLevel() { return m_YLevel; }

    void debugTextGrid(){
        int sizeCount = 0;
        for(auto i = m_Sections.begin(); i != m_Sections.end(); ++i){
            auto section = *i;
            if(sizeCount > m_LateralSize){
                cout << endl;
                sizeCount = 0;
            }

            cout << '[' << section->getStartPosition().x << ',' << section->getStartPosition().z << ']' << "  ";
            sizeCount++;
        }
    }

    void drawGrid(){
        glColor3f(1, 0, 0);
        glPushMatrix();
            float yLevel = getYLevel() + 0.2;
            for(auto section : m_Sections){
                Vector3 startPos = section->getStartPosition();
                Vector3 endPos = section->getEndPosition();
                glBegin(GL_LINE_LOOP);
                    glVertex3f(startPos.x, yLevel, startPos.z);
                    glVertex3f(endPos.x, yLevel, startPos.z);
                    glVertex3f(endPos.x, yLevel, endPos.z);
                    glVertex3f(startPos.x, yLevel, endPos.z);
                glEnd();
            }
        glPopMatrix();
    }

    Section* getSection(Vector3 position){
        Section* selectedSection = nullptr;

        bool hasFounded = false;
        for(int x = 0; x < m_TotalSections; x++){
            Vector3 startPosition = m_Sections[x]->getStartPosition();
            Vector3 endPosition = m_Sections[x]->getEndPosition();

            if(position.x >= startPosition.x && position.x <= endPosition.x
                && position.z >= startPosition.z && position.z <= endPosition.z){
                hasFounded = true;
                selectedSection = m_Sections[x];
            }
        }

        if(!hasFounded){
            selectedSection = m_Sections[0];
        }

        return selectedSection;
    }
};

#endif //FP_OPENGL_GRID_CPP