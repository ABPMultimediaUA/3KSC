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
#include "../headers/extra/Keycodes.hpp"
#include "../headers/extra/Axis.hpp"
#include "../headers/extra/Buttons.hpp"
#include <iostream> // to write in console
#include <cstring> //For std::memcpy()

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

    //Key list
    sf::Keyboard::Key t_keys[101] = {sf::Keyboard::A, sf::Keyboard::B, sf::Keyboard::C, sf::Keyboard::D, sf::Keyboard::E, sf::Keyboard::F, sf::Keyboard::G, sf::Keyboard::H, sf::Keyboard::I, sf::Keyboard::J, sf::Keyboard::K, sf::Keyboard::L, sf::Keyboard::M, sf::Keyboard::N, sf::Keyboard::O, sf::Keyboard::P, sf::Keyboard::Q, sf::Keyboard::R, sf::Keyboard::S, sf::Keyboard::T, sf::Keyboard::U, sf::Keyboard::V, sf::Keyboard::W, sf::Keyboard::X, sf::Keyboard::Y, sf::Keyboard::Z, sf::Keyboard::Num0, sf::Keyboard::Num1, sf::Keyboard::Num2, sf::Keyboard::Num3, sf::Keyboard::Num4, sf::Keyboard::Num5, sf::Keyboard::Num6, sf::Keyboard::Num7, sf::Keyboard::Num8, sf::Keyboard::Num9, sf::Keyboard::Escape, sf::Keyboard::LControl, sf::Keyboard::LShift, sf::Keyboard::LAlt, sf::Keyboard::LSystem , sf::Keyboard::RControl, sf::Keyboard::RShift, sf::Keyboard::RAlt, sf::Keyboard::RSystem , sf::Keyboard::Menu, sf::Keyboard::LBracket, sf::Keyboard::RBracket, sf::Keyboard::SemiColon , sf::Keyboard::Comma, sf::Keyboard::Period, sf::Keyboard::Quote, sf::Keyboard::Slash, sf::Keyboard::BackSlash, sf::Keyboard::Tilde, sf::Keyboard::Equal, sf::Keyboard::Dash, sf::Keyboard::Space, sf::Keyboard::Return, sf::Keyboard::BackSpace, sf::Keyboard::Tab, sf::Keyboard::PageUp, sf::Keyboard::PageDown, sf::Keyboard::End, sf::Keyboard::Home, sf::Keyboard::Insert, sf::Keyboard::Delete, sf::Keyboard::Add, sf::Keyboard::Subtract, sf::Keyboard::Multiply, sf::Keyboard::Divide, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Numpad0, sf::Keyboard::Numpad1, sf::Keyboard::Numpad2, sf::Keyboard::Numpad3, sf::Keyboard::Numpad4, sf::Keyboard::Numpad5, sf::Keyboard::Numpad6, sf::Keyboard::Numpad7, sf::Keyboard::Numpad8, sf::Keyboard::Numpad9, sf::Keyboard::F1, sf::Keyboard::F2, sf::Keyboard::F3, sf::Keyboard::F4, sf::Keyboard::F5, sf::Keyboard::F6, sf::Keyboard::F7, sf::Keyboard::F8, sf::Keyboard::F9, sf::Keyboard::F10, sf::Keyboard::F11, sf::Keyboard::F12, sf::Keyboard::F13, sf::Keyboard::F14, sf::Keyboard::F15, sf::Keyboard::Pause};
    std::memcpy(m_keys, t_keys, 101 * sizeof(sf::Keyboard::Key));

    //Axis list
    sf::Joystick::Axis t_axis[8] = {sf::Joystick::X, sf::Joystick::Y, sf::Joystick::Z, sf::Joystick::R, sf::Joystick::U, sf::Joystick::V, sf::Joystick::PovX, sf::Joystick::PovY};
    std::memcpy(m_axis, t_axis, 8 * sizeof(sf::Joystick::Axis));

    //Devices initialization
    m_inputDevices = new int[4];

    //Conditions initializations
    m_upInput                   = new bool[4];
    m_downInput                 = new bool[4];
    m_leftInput                 = new bool[4];
    m_rightInput                = new bool[4];
    
    m_jumpInput                 = new bool[4];
    m_runInput                  = new bool[4];
    m_blockInput                = new bool[4];
    m_pickInput                 = new bool[4];
    
    m_basicAttackInput          = new bool[4];
    m_specialAttackUpInput      = new bool[4];
    m_specialAttackDownInput    = new bool[4];
    m_specialAttackSideInput    = new bool[4];
    m_ultimateAttackInput       = new bool[4];
    m_waitRelease               = new bool[4];

    for (int i = 0; i < 4; i++){
        m_upInput[i]                = false;
        m_downInput[i]              = false;
        m_leftInput[i]              = false;
        m_rightInput[i]             = false;
        
        m_jumpInput[i]              = false;
        m_runInput[i]               = false;
        m_blockInput[i]             = false;
        m_pickInput[i]              = false;
        
        m_basicAttackInput[i]       = false;
        m_specialAttackUpInput[i]   = false;
        m_specialAttackDownInput[i] = false;
        m_specialAttackSideInput[i] = false;
        m_ultimateAttackInput[i]    = false;
        m_waitRelease[i]            = false;
    }
}

//Destructor
InputManager::~InputManager(){}

//Specific Key press handler
void InputManager::onKeyPressed(int p_key){

}

//Returns whether key with code p_key is pressed or not
bool InputManager::isKeyPressed(int p_key){
    return sf::Keyboard::isKeyPressed(m_keys[p_key]);
}

//Checks if controller with index p_index is connected
bool InputManager::isConnected(int p_joystick){
    return sf::Joystick::isConnected(p_joystick);
}

//Returns wether p_button in p_joystic is pressed or not
bool InputManager::isButtonPressed(int p_joystick, int p_button){
    return sf::Joystick::isButtonPressed(p_joystick, p_button);
}

//Returns the position of the given Axis, in range [-100, 100]
float InputManager::getAxisPosition(int p_joystick, int p_axis){
    return sf::Joystick::getAxisPosition(p_joystick, m_axis[p_axis]);
}

//Updates the state of all joysticks
void InputManager::updateJoysticks(){
    sf::Joystick::update();
}

//Assing input device to player
void assignDevice(int p_device, int p_player, bool p_inGame){
    //Only assign to player 2 while playing for now
    if ((p_inGame && p_player == 1 && p_device == -2) || !p_inGame){
        m_inputDevices[p_player] = p_device;
        //updateInputs(p_player);
    }
}

//Updates joysticks state and booleans for each action
void InputManager::updateInputs(int p_player){
    int t_inputDevice = m_inputDevices[p_player];

    //Keyboard input
    if (t_inputDevice == -1){
    
        /* Controls:
            *   Left/Right or A/D           Movement
            *   Space                       Jump
            *   E                           Basic Attack
            *   X + Up/W                    Up Special Attack
            *   X + Down/S                  Down Special Attack
            *   X + Left/Right or A/D       Side Special Attack
            *   Q                           Pick item
            *   B                           Block
            *   LShift/RShift               Run
            *   Z                           Ultimate Attack
        */

        m_upInput[p_player] = isKeyPressed(Key_W) || isKeyPressed(Key_Up);
        m_downInput[p_player] = isKeyPressed(Key_S) || isKeyPressed(Key_Down);
        m_leftInput[p_player] = isKeyPressed(Key_A) || isKeyPressed(Key_Left);
        m_rightInput[p_player] = isKeyPressed(Key_D) || isKeyPressed(Key_Right);
        
        m_jumpInput[p_player] = isKeyPressed(Key_Space);
        m_runInput[p_player] = isKeyPressed(Key_LShift) || isKeyPressed(Key_RShift);
        m_blockInput[p_player] = isKeyPressed(Key_B);
        m_pickInput[p_player] = isKeyPressed(Key_Q);
        
        m_basicAttackInput[p_player] = isKeyPressed(Key_E);
        m_specialAttackUpInput[p_player] = isKeyPressed(Key_X) && m_upInput[p_player];
        m_specialAttackDownInput[p_player] = isKeyPressed(Key_X) && m_downInput[p_player];
        m_specialAttackSideInput[p_player] = isKeyPressed(Key_X) && (m_leftInput[p_player] || m_rightInput[p_player]);
        m_ultimateAttackInput[p_player] = isKeyPressed(Key_Z);
    }

    //Joystick input
    else if (t_inputDevice != -2){
        //Update joysticks state first
        updateJoysticks();

        /* Controls (XBOX 360 Controller):
            *   Left/Right      Movement
            *   A               Jump
            *   X               Basic Attack
            *   B + Up          Up Special Attack
            *   B + Down        Down Special Attack
            *   B + Left/Right  Side Special Attack
            *   Y               Pick item
            *   LB              Block
            *   RB              Run
            *   LT + RT         Ultimate Attack
        */

        m_upInput[p_player] = getAxisPosition(t_inputDevice, Axis_Y) <= -75 || getAxisPosition(t_inputDevice, Axis_PovY) == -100;
        m_downInput[p_player] = getAxisPosition(t_inputDevice, Axis_Y) >= 75 || getAxisPosition(t_inputDevice, Axis_PovY) == 100;
        m_leftInput[p_player] = getAxisPosition(t_inputDevice, Axis_X) <= -75 || getAxisPosition(t_inputDevice, Axis_PovX) == -100;
        m_rightInput[p_player] = getAxisPosition(t_inputDevice, Axis_X) >= 75 || getAxisPosition(t_inputDevice, Axis_PovX) == 100;

        m_jumpInput[p_player] = isButtonPressed(t_inputDevice, Button_A);
        m_runInput[p_player] = isButtonPressed(t_inputDevice, Button_RB);
        m_blockInput[p_player] = isButtonPressed(t_inputDevice, Button_LB);
        m_pickInput[p_player] = isButtonPressed(t_inputDevice, Button_Y);

        m_basicAttackInput[p_player] = isButtonPressed(t_inputDevice, Button_X);
        m_specialAttackUpInput[p_player] = isButtonPressed(t_inputDevice, Button_B) && m_upInput[p_player];
        m_specialAttackDownInput[p_player] = isButtonPressed(t_inputDevice, Button_B) && m_downInput[p_player];
        m_specialAttackSideInput[p_player] = isButtonPressed(t_inputDevice, Button_B) && (m_leftInput[p_player] || m_rightInput[p_player]);
        m_ultimateAttackInput[p_player] = getAxisPosition(t_inputDevice, Axis_Z) >= 0 && getAxisPosition(m_joystick, Axis_R) >= 0;
    }

    //NPC
    else{
        m_upInput[p_player] = false;
        m_downInput[p_player] = false;
        m_leftInput[p_player] = false;
        m_rightInput[p_player] = false;
        
        m_jumpInput[p_player] = false;
        m_runInput[p_player] = false;
        m_blockInput[p_player] = false;
        m_pickInput[p_player] = false;
        
        m_basicAttackInput[p_player] = false;
        m_specialAttackUpInput[p_player] = false;
        m_specialAttackDownInput[p_player] = false;
        m_specialAttackSideInput[p_player] = false;
        m_ultimateAttackInput[p_player] = false;
    }
}