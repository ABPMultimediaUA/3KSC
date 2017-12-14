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
#include <SFML/Window.hpp>
#include <iostream> // to write in console

//#include <iostream>

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
    
//    for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
//        m_keyIsDown[i] = false;
}

//Destructor
InputManager::~InputManager(){}

//Specific Key press handler
void InputManager::onKeyPressed(int p_key){

}

bool InputManager::isKeyPressed(int p_key){
    
}