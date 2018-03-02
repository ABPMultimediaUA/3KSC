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

#include "../include/managers/EngineManager.hpp"
#include "../include/managers/InputManager.hpp"
#include <iostream>
using namespace irr;

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
bool EngineManager::createWindow(bool p_fullscreen){
 
    core::dimension2d<u32> t_windowSize;
 
    if (p_fullscreen){
        //Create a null device to get the desktop resolution
        IrrlichtDevice* t_nulldevice = createDevice(video::EDT_NULL);
        t_windowSize = t_nulldevice->getVideoModeList()->getDesktopResolution();
        t_nulldevice->drop();
    }
 
    else{
        t_windowSize = core::dimension2d<u32>(640, 480);
    }
 
    //Use the desktop resolution to create a real device
    m_device = createDevice(video::EDT_OPENGL, t_windowSize, 16, p_fullscreen, false, false, this);
    
    //If m_device is NULL
    if(!m_device)
        return false;
 
    m_device->setWindowCaption(L"3KSC");
 
    //Create video driver and scene manager
    m_vDriver = m_device->getVideoDriver();
    m_scene = m_device->getSceneManager();
    
    return true;
}

//Creates a camera
void EngineManager::createCamera(float p_cameraPosition[3], float p_tarjet[3]){
    m_cameraNode = m_scene->addCameraSceneNode();
    if(m_cameraNode){
        m_resetPosition[0] = m_cameraPosition[0] = p_cameraPosition[0];
        m_resetPosition[1] = m_cameraPosition[1] = p_cameraPosition[1];
        m_resetPosition[2] = m_cameraPosition[2] = p_cameraPosition[2];
        m_resetPosition[3] = m_cameraPosition[3] = p_tarjet[0];
        m_resetPosition[4] = m_cameraPosition[4] = p_tarjet[1];
        m_resetPosition[5] = m_cameraPosition[5] = p_tarjet[2];
        m_cameraNode->setPosition(core::vector3df(p_cameraPosition[0],p_cameraPosition[1],p_cameraPosition[2]));
        m_cameraNode->setTarget(core::vector3df(p_tarjet[0],p_tarjet[1],p_tarjet[2]));
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
    if(m_cameraNode && m_moveCamera){
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
    }
}

//Returns whether the device is running or not
bool EngineManager::running(){
    return m_device->run();
}

//Drops the device
void EngineManager::stop(){
    m_device->drop();
}

//Irrlicht events
bool EngineManager::OnEvent(const SEvent& p_event){}

//Sets m_prevTime for the first time
void EngineManager::timeStamp(){
    m_prevTime = EngineManager::instance()->getDevice()->getTimer()->getTime();
}

//Sets frame delta time of the last frame (in seconds) and prepares it for next update
float EngineManager::updateFrameDeltaTime(){
    m_nowTime = EngineManager::instance()->getDevice()->getTimer()->getTime();
    m_frameDeltaTime = (f32)(m_nowTime-m_prevTime)/1000.f;
    m_prevTime = m_nowTime;
}

//Creates a new node
void EngineManager::createEntity(int p_id, float p_position[3]){
    scene::ISceneNode* t_node = m_scene->addCubeSceneNode();

    if (t_node){
        //Add node to class node vector
        m_entityNodes.push_back(t_node);

        t_node->setPosition(core::vector3df(p_position[0],p_position[1],p_position[2]));
        t_node->setMaterialFlag(video::EMF_LIGHTING, false);
    }
}

void EngineManager::deleteEntity(int p_id){
    m_entityNodes.at(p_id)->remove();
}

//Loads a 3D model
void EngineManager::load3DModel(int p_id, float p_position[3], float p_scale[3], const char* p_modelURL){
    scene::IAnimatedMesh* t_mesh = m_scene->getMesh(p_modelURL);
    scene::ISceneNode* t_node = 0;

    if (t_mesh){
        t_node = m_scene->addOctreeSceneNode(t_mesh->getMesh(0), 0, p_id, 1024);
        t_node->setPosition(core::vector3df(p_position[0], p_position[1], p_position[2]));
        t_node->setMaterialFlag(video::EMF_LIGHTING, false);
        t_node->setScale(core::vector3df(p_scale[0], p_scale[1], p_scale[2]));

        //Add node to class node vector 
        m_entityNodes.push_back(t_node);
    }
}

void EngineManager::loadArena(const char* p_arenaModelURL){
    scene::IAnimatedMesh* t_map = m_scene->getMesh(p_arenaModelURL);
    scene::ISceneNode* t_node = 0;

    if (t_map){
        t_node = m_scene->addOctreeSceneNode(t_map->getMesh(0), 0, -1, 1024);
        t_node->setPosition(core::vector3df(0,0,10));
        t_node->setMaterialFlag(video::EMF_LIGHTING, false);
        t_node->setScale(core::vector3df(10,10,10));

        //Add node to class node vector 
        m_entityNodes.push_back(t_node);
    }
}

void EngineManager::loadSkybox(const char* p_skyboxURLs[6]){
    m_vDriver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, false);

    scene::ISceneNode* t_skybox = m_scene->addSkyBoxSceneNode(
        m_vDriver->getTexture(p_skyboxURLs[0]),
        m_vDriver->getTexture(p_skyboxURLs[1]),
        m_vDriver->getTexture(p_skyboxURLs[2]),
        m_vDriver->getTexture(p_skyboxURLs[3]),
        m_vDriver->getTexture(p_skyboxURLs[4]),
        m_vDriver->getTexture(p_skyboxURLs[5]));

    m_vDriver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, true);

    //m_entityNodes.push_back(t_skybox);
}

void EngineManager::moveEntity(Entity* p_entity){
    core::vector3df t_position;
    float*          t_entityPosition = p_entity->getPosition();
    t_position.X = (f32) t_entityPosition[0];
    t_position.Y = (f32) t_entityPosition[1];
    t_position.Z = (f32) t_entityPosition[2];

    m_entityNodes.at(p_entity->getId())->setPosition(t_position);
}

void EngineManager::setRotation(int p_id, float p_degrees){
    scene::ISceneNode* t_node  = m_entityNodes.at(p_id);
    
    t_node->setRotation(core::vector3df(0.0f, p_degrees, 0.0f));
}

void EngineManager::scale(int p_id, float p_scale[3]){
    scene::ISceneNode* t_node  = m_entityNodes.at(p_id);

    t_node->setScale(core::vector3df(p_scale[0], p_scale[1], p_scale[2]));
}

//Scene render function
void EngineManager::drawScene(){
    m_vDriver->beginScene(true, true, video::SColor(255,79,195,247));
    m_scene->drawAll();
    m_vDriver->endScene();
}

//Returns game window
//sf::RenderWindow* EngineManager::getWindow(){
//   return m_window;
//}

float EngineManager::getFrameDeltaTime(){
    return (float) m_frameDeltaTime;
}

irr::scene::ISceneManager* EngineManager::getSceneManager(){
    return m_scene;
}

scene::ISceneNode* EngineManager::getEntityNode(int p_id){
    return m_entityNodes.at(p_id);
}










irr::video::IVideoDriver* EngineManager::getVideoDriver(){
    return m_vDriver;
}

void EngineManager::loadCharacter(){
}

void EngineManager::loadObject(){

}

void EngineManager::putCharacter(){

}

void EngineManager::putObject(){

}

void EngineManager::drawArena(){

}

void EngineManager::drawCharacter(){

}

void EngineManager::drawObject(){

}

IrrlichtDevice* EngineManager::getDevice(){
    return m_device;
}