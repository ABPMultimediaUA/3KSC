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

//Handles player movement from input devices
void InputManager::playerMove(Character* p_player){
//    //void* ???
//    core::vector3df t_nodePosition = p_player->getNode()->getPosition();
//
//    //Exit
//    if(m_instance->IsKeyDown(irr::KEY_ESCAPE))
//        //device->drop();
//
//    //Jump    
//    if(m_instance->IsKeyDown(irr::KEY_SPACE))
//        t_nodePosition.Y += MOVEMENT_SPEED*3 * frameDeltaTime;
//
//    m_runningFactor = 1;
//    
//    //Sprint
//    if(m_instance->IsKeyDown(irr::KEY_LSHIFT))
//        m_runningFactor = 2;
//
//    //Left
//    if(m_instance->IsKeyDown(irr::KEY_KEY_A))
//        t_nodePosition.X -= MOVEMENT_SPEED * frameDeltaTime * m_runningFactor;
//
//    //Right    
//    else if(m_instance->IsKeyDown(irr::KEY_KEY_D))
//        t_nodePosition.X += MOVEMENT_SPEED * frameDeltaTime * m_runningFactor;
//
//    p_player->getNode()->setPosition(t_nodePosition);
}


//Specific Key press handler
void InputManager::onKeyPressed(int p_key){

}