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
    if (!m_instance)
        m_instance = new EngineManager();

    return m_instance;
}

//Constructor
EngineManager::EngineManager(){

}

//Destructor
EngineManager::~EngineManager(){}

//Creates the game window
bool EngineManager::createWindow(){
    //Create a null device to get the desktop resolution
    //IrrlichtDevice* t_nulldevice = createDevice(video::EDT_NULL);
    //core::dimension2d<u32> t_desktopResolution = t_nulldevice->getVideoModeList()->getDesktopResolution();
    //t_nulldevice->drop();

    //Use the desktop resolution to create a real device
    //IrrlichtDevice* t_device = createDevice(video::EDT_OPENGL, t_desktopResolution, 16, true, false, false, &inputs);
    m_device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(640, 480), 16, false, false, false, InputManager::instance());

    //0 usually means "success", but with pointers, it's a null pointer.
    if(!m_device)
        return false;

    m_device->setWindowCaption(L"3KSC");

    //Create video driver and scene manager
    m_vDriver = m_device->getVideoDriver();
    m_scene = m_device->getSceneManager();
    
    return true;
}

//Scene render function
void EngineManager::drawScene(){
    m_vDriver->beginScene(true, true, video::SColor(255,0,150,136));
    m_scene->drawAll();
    m_vDriver->endScene();
}

//Returns whether the device is running or not
bool EngineManager::deviceIsRunning(){
    return m_device->run();
}

//Drops the device
void EngineManager::dropDevice(){
    m_device->drop();
}

//Creates a new node
void EngineManager::createCubeNode(int p_id, float p_position[3]){
    scene::ISceneNode* t_node = m_scene->addCubeSceneNode();

    if (t_node){
        //Add node to class node vector 
        m_entityNodes.push_back(t_node);

        t_node->setPosition(core::vector3df(p_position[0],p_position[1],p_position[2]));
        t_node->setMaterialFlag(video::EMF_LIGHTING, false);
    }
}

void EngineManager::scaleNode(int p_id, float p_scale[3]){
    scene::ISceneNode* t_node  = m_entityNodes.at(p_id);

    t_node->setScale(core::vector3df(p_scale[0], p_scale[1], p_scale[2]));
}

void EngineManager::createCamera(){
    scene::ICameraSceneNode * cameraNode = m_scene->addCameraSceneNode();
    if(cameraNode){
        cameraNode->setPosition(core::vector3df(0,35,-100));
        cameraNode->setTarget(core::vector3df(0,0,0));
    }
}

void EngineManager::loadArena(){

}

void EngineManager::loadCharacters(){

}

void EngineManager::loadObjects(){

}

void EngineManager::putCharacters(){

}

void EngineManager::putObject(){

}

void EngineManager::drawArena(){

}

void EngineManager::drawCharacter(){

}

void EngineManager::drawObject(){

}

scene::ISceneNode* EngineManager::getEntityNode(int p_id){
    return m_entityNodes.at(p_id);
}

IrrlichtDevice* EngineManager::getDevice(){
    return m_device;
}