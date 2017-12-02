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

#include "../headers/managers/InputManager.hpp"
#include "../headers/managers/EngineManager.hpp"
using namespace irr;

//Instance initialization
InputManager* InputManager::m_instance = 0;

//Returns the only instance of this class
InputManager* InputManager::instance(){
    if (!m_instance)
        m_instance = new InputManager();

    return m_instance;
}


//Constructor
InputManager::InputManager(){
    m_bindings = 0;
    
    for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
        m_keyIsDown[i] = false;

    m_moveSpeed = 50.f;
    m_runningFactor = 1;
}

//Destructor
InputManager::~InputManager(){}


//Detects events and acts if its a keyboard event
bool InputManager::OnEvent(const SEvent& p_event){
    if (p_event.EventType == irr::EET_KEY_INPUT_EVENT)
        m_keyIsDown[p_event.KeyInput.Key] = p_event.KeyInput.PressedDown;

    return false;
}

// Check whether a key is being held down
bool InputManager::IsKeyDown(EKEY_CODE p_keyCode) const{
    return m_keyIsDown[p_keyCode];
}

//Specific Key press handler
void InputManager::onKeyPressed(int p_key){

}

//Sets m_prevTime for the first time
void InputManager::timeStamp(){
    m_prevTime = EngineManager::instance()->getDevice()->getTimer()->getTime();
}

//Sets frame delta time of the last frame (in seconds) and prepares it for next update
void InputManager::updateFrameDeltaTime(){
    m_nowTime = EngineManager::instance()->getDevice()->getTimer()->getTime();
    m_frameDeltaTime = (f32)(m_nowTime-m_prevTime)/1000.f;
    m_prevTime = m_nowTime;
}

//Handles player movement from input devices
void InputManager::playerMove(Character* p_player){
    //Get player position from node
    core::vector3df t_nodePosition = EngineManager::instance()->getEntityNode(p_player->getId())->getPosition();

    //Exit
    if(IsKeyDown(irr::KEY_ESCAPE))
        EngineManager::instance()->dropDevice();

    //Jump    
    if(IsKeyDown(irr::KEY_SPACE))
        t_nodePosition.Y += m_moveSpeed * 3 * m_frameDeltaTime;

    m_runningFactor = 1;
    
    //Sprint
    if(IsKeyDown(irr::KEY_LSHIFT) || IsKeyDown(irr::KEY_RSHIFT))
        m_runningFactor = 2;

    //Up
    if(IsKeyDown(irr::KEY_KEY_W) || IsKeyDown(irr::KEY_UP))
        t_nodePosition.Y += m_moveSpeed * m_frameDeltaTime * m_runningFactor;

    //Down
    if(IsKeyDown(irr::KEY_KEY_S) || IsKeyDown(irr::KEY_DOWN))
        t_nodePosition.Y -= m_moveSpeed * m_frameDeltaTime * m_runningFactor;

    //Left
    if(IsKeyDown(irr::KEY_KEY_A) || IsKeyDown(irr::KEY_LEFT))
        t_nodePosition.X -= m_moveSpeed * m_frameDeltaTime * m_runningFactor;

    //Right    
    if(IsKeyDown(irr::KEY_KEY_D) || IsKeyDown(irr::KEY_RIGHT))
        t_nodePosition.X += m_moveSpeed * m_frameDeltaTime * m_runningFactor;

    EngineManager::instance()->getEntityNode(p_player->getId())->setPosition(t_nodePosition);
}