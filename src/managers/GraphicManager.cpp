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

#include "../headers/managers/GraphicManager.hpp"
#include "../headers/managers/EngineManager.hpp"

//Instance initialization
GraphicManager* GraphicManager::m_instance = 0;

//Returns the only instance of this class
GraphicManager* GraphicManager::instance(){
    if (!m_instance)
        m_instance = new GraphicManager();

    return m_instance;
}


//Constructor
GraphicManager::GraphicManager(){
    m_scale = 1.0;
}

//Destructor
GraphicManager::~GraphicManager(){}

bool GraphicManager::createWindow(){
    return EngineManager::instance()->createWindow();
}

void GraphicManager::createCamera(){
    EngineManager::instance()->createCamera();
}

void GraphicManager::createCube(float p_position[3]){
    EngineManager::instance()->createCubeNode(p_position);
}

bool GraphicManager::running(){
    return EngineManager::instance()->deviceIsRunning();
}

void GraphicManager::draw(){
    EngineManager::instance()->drawScene();
}

void GraphicManager::stop(){
    EngineManager::instance()->dropDevice();
}

//void GraphicManager::addSpriteSheet(Spritesheet* p_spriteSheet){
//
//}
//
//void GraphicManager::addSprite(Sprite* p_sprite){
//}
//
//void GraphicManager::addMode(Mode* p_mode){
//    
//}
//
//void GraphicManager::addText(Text* p_text){
//}