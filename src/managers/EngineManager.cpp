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

#include "../headers/managers/EngineManager.hpp"
#include "../headers/managers/InputManager.hpp"
using namespace irr;

//Instance initialization
EngineManager* EngineManager::m_instance = 0;

//Returns the only instance of this class
EngineManager* EngineManager::instance(){
    if (!m_instance){
        m_instance = new EngineManager();
    }

    return m_instance;
}

//Constructor
EngineManager::EngineManager(){
    
}

//Destructor
EngineManager::~EngineManager(){}

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

//Creates the game window
bool EngineManager::createWindow(){
    m_device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(640, 480), 16, false, false, false, this);
    //If m_device is NULL
    if(!m_device)
        return false;

    m_device->setWindowCaption(L"3KSC");

    //Create video driver and scene manager
    m_vDriver = m_device->getVideoDriver();
    m_scene = m_device->getSceneManager();
    
    return true;
}

irr::video::IVideoDriver* EngineManager::getVideoDriver(){
    return m_vDriver;
}

irr::scene::ISceneManager* EngineManager::getSceneManager(){
    return m_scene;
}

void EngineManager::createCamera(){
    scene::ICameraSceneNode * cameraNode = m_scene->addCameraSceneNode();
    if(cameraNode){
        cameraNode->setPosition(core::vector3df(0,90,-150));
        cameraNode->setTarget(core::vector3df(0,50,0));
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

//Loads a 3D model
void EngineManager::load3DModel(int p_id, float p_position[3], float p_scale, const char* p_modelURL){
    scene::IAnimatedMesh* t_mesh = m_scene->getMesh(p_modelURL);
    scene::ISceneNode* t_node = 0;

    if (t_mesh){
        t_node = m_scene->addOctreeSceneNode(t_mesh->getMesh(0), 0, p_id, 1024);
        t_node->setPosition(core::vector3df(p_position[0], p_position[1], p_position[2]));
        t_node->setMaterialFlag(video::EMF_LIGHTING, false);
        t_node->setScale(core::vector3df(p_scale, p_scale, p_scale));

        //Add node to class node vector 
        m_entityNodes.push_back(t_node);
    }
}

void EngineManager::loadArena(const char* arenaModelURL){
    scene::IAnimatedMesh* t_map = m_scene->getMesh(arenaModelURL);
    scene::ISceneNode* t_node = 0;

    if (t_map){
        t_node = m_scene->addOctreeSceneNode(t_map->getMesh(0), 0, -1, 1024);
        t_node->setPosition(core::vector3df(0,0,0));
        t_node->setMaterialFlag(video::EMF_LIGHTING, false);
        t_node->setScale(core::vector3df(10,10,10));
    }
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

void EngineManager::moveEntity(Entity* p_entity){
    core::vector3df t_position;
    float*          t_entityPosition = p_entity->getPosition();
    t_position.X = (f32) t_entityPosition[0];
    t_position.Y = (f32) t_entityPosition[1];
    t_position.Z = (f32) t_entityPosition[2];

    m_entityNodes.at(p_entity->getId()-1)->setPosition(t_position);
}

scene::ISceneNode* EngineManager::getEntityNode(int p_id){
    return m_entityNodes.at(p_id);
}

IrrlichtDevice* EngineManager::getDevice(){
    return m_device;
}

float EngineManager::getFrameDeltaTime(){
    return (float) m_frameDeltaTime;
}