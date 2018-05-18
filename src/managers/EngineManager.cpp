/*
    3KSC: A fighting game
    Copyright (C) 2018  Chaotic Games

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see http://www.gnu.org/licenses/.

    You can contact Chaotic Games at: chaoticgamesdev@gmail.com
*/

#include <CE.hpp>
#include "../include/managers/EngineManager.hpp"
#include "../include/managers/InputManager.hpp"
#include "../include/extra/ResolutionPresets.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

//Returns the only instance of this class
EngineManager& EngineManager::instance(){
    static EngineManager instance;
    return instance;
}

//Constructor
EngineManager::EngineManager(){
    m_moveCamera = false;
}

//Destructor
EngineManager::~EngineManager(){}

//Creates the game window
void EngineManager::createWindow(int p_resolutionPreset, bool p_fullscreen){
    int t_width     = g_resolutionPresets[p_resolutionPreset].width,
        t_height    = g_resolutionPresets[p_resolutionPreset].height;

    m_window = new CEWindow(t_width, t_height, "3KSC", p_fullscreen);
    // m_window = new CEWindow(640, 480, "3KSC", p_fullscreen);
    m_scene  = new CEScene();
}

CEPosition EngineManager::getWindowPosition(){
    return m_window->getPosition();
}

CESize EngineManager::getWindowSize(){
    return m_window->getSize();
}

bool EngineManager::isWindowActive(){
    return m_window->isOpen();
}

//Hides or shows the cursor
void EngineManager::setCursorVisible(bool p_visible){
    m_window->setCursorVisible(p_visible);
}

//Returns whether the device is running or not
bool EngineManager::running(){
    return m_window->isOpen();
}

void EngineManager::swapBuffers(){
    m_window->swapBuffers();
}

void EngineManager::pollEvents(){
    m_window->pollEvents();
}


//Drops the device
void EngineManager::stop(){
    m_scene->release();
    m_window->close();
}

//Creates a camera
void EngineManager::createCamera(float p_cameraPosition[3], float p_tarjet[3]){
    m_cameraNode = m_scene->createCamera(true);
    if(m_cameraNode){
        m_resetPosition[0] = m_cameraPosition[0] = p_cameraPosition[0];
        m_resetPosition[1] = m_cameraPosition[1] = p_cameraPosition[1];
        m_resetPosition[2] = m_cameraPosition[2] = p_cameraPosition[2];
        m_resetPosition[3] = m_cameraPosition[3] = p_tarjet[0];
        m_resetPosition[4] = m_cameraPosition[4] = p_tarjet[1];
        m_resetPosition[5] = m_cameraPosition[5] = p_tarjet[2];
        m_cameraNode->setAbsolutePosition(p_cameraPosition[0],p_cameraPosition[1],p_cameraPosition[2]);
        m_cameraNode->lookAt(p_tarjet[0],p_tarjet[1],p_tarjet[2]);
    }
}

void EngineManager::moveCamera(float p_posX, float p_posY, float p_posZ){
    if(m_cameraNode){
        m_moveCamera = true;
        m_amountTime = 0.0;

        m_newCameraPosition[0] = p_posX;
        m_newCameraPosition[1] = p_posY+35;
        m_newCameraPosition[2] = p_posZ-75;
        m_newCameraPosition[3] = p_posX;
        m_newCameraPosition[4] = p_posY;
        m_newCameraPosition[5] = p_posZ;

        //m_cameraNode->setPosition(core::vector3df(p_posX, p_posY+35,p_posZ-75));
        //m_cameraNode->setTarget(core::vector3df(p_posX, p_posY,p_posZ));
    }
}

void EngineManager::resetCamera(){
    if(m_cameraNode){
        m_moveCamera = true;
        m_amountTime = 0.0;

        m_newCameraPosition[0] = m_resetPosition[0];
        m_newCameraPosition[1] = m_resetPosition[1];
        m_newCameraPosition[2] = m_resetPosition[2];
        m_newCameraPosition[3] = m_resetPosition[3];
        m_newCameraPosition[4] = m_resetPosition[4];
        m_newCameraPosition[5] = m_resetPosition[5];
        
        //m_cameraNode->setPosition(core::vector3df(m_resetPosition[0], m_resetPosition[1], m_resetPosition[2]));
        //m_cameraNode->setTarget(core::vector3df(m_resetPosition[3], m_resetPosition[4], m_resetPosition[5]));
    }
}

void EngineManager::updateCamera(){
    /*if(m_cameraNode && m_moveCamera){
        float t_maxTime = 1.0;
        m_amountTime += getFrameDeltaTime();

        float posXCamera = (t_maxTime-m_amountTime)*m_cameraPosition[0] + m_amountTime*m_newCameraPosition[0];
        float posYCamera = (t_maxTime-m_amountTime)*m_cameraPosition[1] + m_amountTime*m_newCameraPosition[1];
        float posZCamera = (t_maxTime-m_amountTime)*m_cameraPosition[2] + m_amountTime*m_newCameraPosition[2];

        float posXTarget = (t_maxTime-m_amountTime)*m_cameraPosition[3] + m_amountTime*m_newCameraPosition[3];
        float posYTarget = (t_maxTime-m_amountTime)*m_cameraPosition[4] + m_amountTime*m_newCameraPosition[4];
        float posZTarget = (t_maxTime-m_amountTime)*m_cameraPosition[5] + m_amountTime*m_newCameraPosition[5];

        m_cameraNode->setPosition(core::vector3df(posXCamera, posYCamera, posZCamera));
        m_cameraNode->setTarget(core::vector3df(posXTarget, posYTarget, posZTarget));

        if(m_amountTime >= t_maxTime){
            m_amountTime = 0.0;
            m_moveCamera = false;

            m_cameraPosition[0] = m_newCameraPosition[0];
            m_cameraPosition[1] = m_newCameraPosition[1];
            m_cameraPosition[2] = m_newCameraPosition[2];
            m_cameraPosition[3] = m_newCameraPosition[3];
            m_cameraPosition[4] = m_newCameraPosition[4];
            m_cameraPosition[5] = m_newCameraPosition[5];
        }
    }*/
}

void EngineManager::createGlobalLight(float p_lightPosition[3], float p_lightDirection[3]){
    CESceneLight* t_light = m_scene->createDirectionalLight(p_lightDirection);
    if(t_light){
        t_light->setAbsolutePosition(p_lightPosition[0],p_lightPosition[1],p_lightPosition[2]);
    }
}

void EngineManager::createPointLight(float p_lightPosition[3], float p_lightAtenuation){
    CESceneLight* t_light = m_scene->createPointLight(p_lightAtenuation);
    if(t_light){
        t_light->setAbsolutePosition(p_lightPosition[0],p_lightPosition[1],p_lightPosition[2]);
    }
}

//Sets frame delta time of the last frame (in seconds) and prepares it for next update
float EngineManager::updateFrameDeltaTime(float p_delta){
    m_frameDeltaTime = p_delta;
}

void EngineManager::deleteEntity(int p_id){
    //std::cout << "IMPLEMENTAR DELETE EN MESH EN NUETRO MOTOR" << std::endl;
    //m_entityNodes.at(p_id)->remove();
    m_scene->remove(m_entityNodes.at(p_id)->getTopNode());
}

//Loads a 3D model
void EngineManager::load3DModel(int p_id, float p_position[3], float p_scale[3], const char* p_modelURL){
    CESceneMesh* t_mesh = m_scene->createMesh(p_modelURL);

    if(t_mesh){
        t_mesh->setAbsolutePosition(p_position[0], p_position[1], p_position[2]);
        t_mesh->setAbsoluteScale(p_scale[0], p_scale[1], p_scale[2]);
        //std::cout << "Posit: " << p_position[0] << ", " << p_position[1] << ", " << p_position[2] << std::endl;
        //std::cout << "Scale: " << p_scale[0] << ", " << p_scale[1] << ", " << p_scale[2] << std::endl;

        m_entityNodes.push_back(t_mesh);
    }
}

void EngineManager::loadSkybox(const char* p_skyboxURLs[6]){
    //CESceneSkybox* t_skybox = m_scene->createSkybox(p_skyboxURLs);

    //m_entityNodes.push_back(t_skybox);
}

void EngineManager::moveEntity(Entity* p_entity){
    /*
    float* t_position = p_entity->getElapsedPosition();
    m_entityNodes.at(p_entity->getId())->setPosition(t_position[0], t_position[1], t_position[2]);
    */

    float* t_position = p_entity->getPosition();
    m_entityNodes.at(p_entity->getId())->setAbsolutePosition(t_position[0], t_position[1], t_position[2]);
}

void EngineManager::setRotation(int p_id, float p_degrees){
    CESceneMesh* t_node  = m_entityNodes.at(p_id);
    
    t_node->setAbsoluteRotation(0.0f, p_degrees, 0.0f);
}

void EngineManager::scale(int p_id, float p_scale[3]){
    CESceneMesh* t_node  = m_entityNodes.at(p_id);

    t_node->setAbsoluteScale(p_scale[0], p_scale[1], p_scale[2]);
}

//Scene render function
void EngineManager::drawScene(){
    m_window->clear(0.0f, 0.8f, 0.9f, 1.0f);
    m_scene->draw();
}

void EngineManager::drawScene2D(){
    m_window->clear(0.5f, 0.8f, 0.9f, 1.0f);
    m_scene->draw2D();
}

void EngineManager::cleanScene(){
    m_scene->clean();
}

float EngineManager::getFrameDeltaTime(){
    return (float)m_frameDeltaTime * 5;
}

CESceneMesh* EngineManager::getEntityNode(int p_id){
    return m_entityNodes.at(p_id);
}

void EngineManager::getEntityPosition(int p_id){
    m_entityNodes.at(p_id)->getPosition();
}

void EngineManager::parseOBJ(const char* p_filename){
    m_VertexX.clear();
    m_VertexY.clear();
    m_VertexZ.clear();

    bool t_newObject = false;

    float t_X    =  0.0,   t_Y    =  0.0,   t_Z    =  0.0;
    float t_maxX = -999.0, t_maxY = -999.0, t_maxZ = -999.0;
    float t_minX =  999.0, t_minY =  999.0, t_minZ =  999.0;

    std::ifstream t_file(p_filename);
    std::string t_line;
    std::string t_name;
    bool pisa = false;
    while(std::getline(t_file, t_line)){
        if(t_line == "" || t_line[0] == '#')// Skip everything and continue with the next line
            continue;

        std::istringstream t_tokens(t_line);
        std::vector<std::string> t_elements(std::istream_iterator<std::string>{t_tokens}, std::istream_iterator<std::string>());

        if(t_elements[0].compare("o") == 0){
            if(t_elements[1].compare("pisa") == 0){
                pisa = true;
                if(m_totalVertex != 0){
                    pushVertex(t_minX, t_maxX, t_minY, t_maxY, t_minZ, t_maxZ);

                    t_maxX = -999.0, t_maxY = -999.0, t_maxZ = -999.0;
                    t_minX =  999.0, t_minY =  999.0, t_minZ =  999.0;
                }
                m_totalVertex++;
            }
            else if(t_elements[1].compare("no") == 0){
                pisa = false;
            }
        }

        if(t_elements[0].compare("v") == 0 && pisa){// Vertex
            sscanf(t_line.c_str(), "%*s %f %f %f", &t_X, &t_Y, &t_Z);

            compareMaxAndMin(t_X, t_maxX, t_minX);
            compareMaxAndMin(t_Y, t_maxY, t_minY);
            compareMaxAndMin(t_Z, t_maxZ, t_minZ);
        }
    }
    pushVertex(t_minX, t_maxX, t_minY, t_maxY, t_minZ, t_maxZ);
}

void EngineManager::compareMaxAndMin(float p_value, float &p_max, float &p_min){
    if(p_value > p_max)
        p_max = p_value;

    if(p_value < p_min)
        p_min = p_value;
}

void EngineManager::pushVertex(float p_minX, float p_maxX, float p_minY, float p_maxY, float p_minZ, float p_maxZ){
    m_VertexX.push_back(p_minX);
    m_VertexX.push_back(p_maxX);

    m_VertexY.push_back(p_minY);
    m_VertexY.push_back(p_maxY);

    m_VertexZ.push_back(p_minZ);
    m_VertexZ.push_back(p_maxZ);

    /*
    std::cout <<
        "Objeto: " << m_totalVertex << "\n" <<
        "PosMin: " << p_minX << "," << p_minY << "," << p_minZ << "\n" <<
        "PosMax: " << p_maxX << "," << p_maxY << "," << p_maxZ << "\n" <<
        "---------------------------------\n";
    */
}

void EngineManager::createDebugQuad(float p_vertex[4][2]){
    CESceneQuad* t_quad = m_scene->createQuad(p_vertex);
}

CESceneSprite* EngineManager::createSprite(const char* p_url, float p_width, float p_height){
    return m_scene->createSprite(p_url, p_width, p_height);
}

void EngineManager::createParticleSystem(const char* p_url, int p_amount){
    m_system = m_scene->createParticleSystem(p_url, p_amount);
}

void EngineManager::updateParticleSystem(){
    m_system->update();
}

double EngineManager::getTime(){
    return m_window->getTimer();
}

double EngineManager::getElapsedTime(){
    return m_window->getElapsedTime();
}