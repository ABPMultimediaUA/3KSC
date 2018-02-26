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

#include "../include/managers/InputManager.hpp"
#include "../include/managers/EngineManager.hpp"
#include "../include/extra/Keycodes.hpp"
#include "../include/extra/Axis.hpp"
#include "../include/extra/Buttons.hpp"
#include "../include/extra/Actions.hpp"
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

    //Event handling
    m_window    = new sf::Window();
    m_event     = new sf::Event();

    //Key list
    sf::Keyboard::Key t_keys[101] = {sf::Keyboard::A, sf::Keyboard::B, sf::Keyboard::C, sf::Keyboard::D, sf::Keyboard::E, sf::Keyboard::F, sf::Keyboard::G, sf::Keyboard::H, sf::Keyboard::I, sf::Keyboard::J, sf::Keyboard::K, sf::Keyboard::L, sf::Keyboard::M, sf::Keyboard::N, sf::Keyboard::O, sf::Keyboard::P, sf::Keyboard::Q, sf::Keyboard::R, sf::Keyboard::S, sf::Keyboard::T, sf::Keyboard::U, sf::Keyboard::V, sf::Keyboard::W, sf::Keyboard::X, sf::Keyboard::Y, sf::Keyboard::Z, sf::Keyboard::Num0, sf::Keyboard::Num1, sf::Keyboard::Num2, sf::Keyboard::Num3, sf::Keyboard::Num4, sf::Keyboard::Num5, sf::Keyboard::Num6, sf::Keyboard::Num7, sf::Keyboard::Num8, sf::Keyboard::Num9, sf::Keyboard::Escape, sf::Keyboard::LControl, sf::Keyboard::LShift, sf::Keyboard::LAlt, sf::Keyboard::LSystem , sf::Keyboard::RControl, sf::Keyboard::RShift, sf::Keyboard::RAlt, sf::Keyboard::RSystem , sf::Keyboard::Menu, sf::Keyboard::LBracket, sf::Keyboard::RBracket, sf::Keyboard::SemiColon , sf::Keyboard::Comma, sf::Keyboard::Period, sf::Keyboard::Quote, sf::Keyboard::Slash, sf::Keyboard::BackSlash, sf::Keyboard::Tilde, sf::Keyboard::Equal, sf::Keyboard::Dash, sf::Keyboard::Space, sf::Keyboard::Return, sf::Keyboard::BackSpace, sf::Keyboard::Tab, sf::Keyboard::PageUp, sf::Keyboard::PageDown, sf::Keyboard::End, sf::Keyboard::Home, sf::Keyboard::Insert, sf::Keyboard::Delete, sf::Keyboard::Add, sf::Keyboard::Subtract, sf::Keyboard::Multiply, sf::Keyboard::Divide, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Numpad0, sf::Keyboard::Numpad1, sf::Keyboard::Numpad2, sf::Keyboard::Numpad3, sf::Keyboard::Numpad4, sf::Keyboard::Numpad5, sf::Keyboard::Numpad6, sf::Keyboard::Numpad7, sf::Keyboard::Numpad8, sf::Keyboard::Numpad9, sf::Keyboard::F1, sf::Keyboard::F2, sf::Keyboard::F3, sf::Keyboard::F4, sf::Keyboard::F5, sf::Keyboard::F6, sf::Keyboard::F7, sf::Keyboard::F8, sf::Keyboard::F9, sf::Keyboard::F10, sf::Keyboard::F11, sf::Keyboard::F12, sf::Keyboard::F13, sf::Keyboard::F14, sf::Keyboard::F15, sf::Keyboard::Pause};
    std::memcpy(m_keys, t_keys, 101 * sizeof(sf::Keyboard::Key));

    //Axis list
    sf::Joystick::Axis t_axis[8] = {sf::Joystick::X, sf::Joystick::Y, sf::Joystick::Z, sf::Joystick::R, sf::Joystick::U, sf::Joystick::V, sf::Joystick::PovX, sf::Joystick::PovY};
    std::memcpy(m_axis, t_axis, 8 * sizeof(sf::Joystick::Axis));

    //Devices initialization
    m_inputDevices[0]   = -1;
    m_inputDevices[1]   =  0;
    m_inputDevices[2]   = -2;
    m_inputDevices[3]   = -2;

    //Initialize action booleans
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < (int) Action::Count; j++){
            m_actions[i][j] = false;
        }
    }
}

//Destructor
InputManager::~InputManager(){}

//Catches events and returns true if an event happened
bool InputManager::eventHandler(){
    bool t_eventReceived = false;

    while (m_window->pollEvent(*m_event)){
        switch (m_event->type){
            //Keyboard key pressed
            case sf::Event::KeyPressed:{
                std::cout << "Check" << std::endl;
                updateKeyInputs(m_event->key.code, true);

                t_eventReceived = true;
                break;
            }

            //Keyboard key released
            case sf::Event::KeyReleased:{         
                updateKeyInputs(m_event->key.code, false);
                
                t_eventReceived = true;
                break;
            }


            //New Joystick connected
            case sf::Event::JoystickConnected:{

                t_eventReceived = true;
                break;
            }

            //Lost Joystick connection
            case sf::Event::JoystickDisconnected:{

                t_eventReceived = true;
                break;
            }

            //Joystick button pressed
            case sf::Event::JoystickButtonPressed:{

                t_eventReceived = true;
                break;
            }

            //Joystick axis changed
            case sf::Event::JoystickMoved:{

                t_eventReceived = true;
                break;
            }
        }
    }

    return t_eventReceived;
}

//Specific Key press handler
void InputManager::onKeyPressed(int p_key){

}

//Returns whether key with code p_key is pressed or not
bool InputManager::isKeyPressed(Key p_key){
    return sf::Keyboard::isKeyPressed(m_keys[(int) p_key]);
}

//Checks if controller with index p_index is connected
bool InputManager::isConnected(int p_joystick){
    return sf::Joystick::isConnected(p_joystick);
}

//Returns wether p_button in p_joystic is pressed or not
bool InputManager::isButtonPressed(int p_joystick, Button p_button){
    return sf::Joystick::isButtonPressed(p_joystick, (int) p_button);
}

//Returns the position of the given Axis, in range [-100, 100]
float InputManager::getAxisPosition(int p_joystick, Axis p_axis){
    return sf::Joystick::getAxisPosition(p_joystick, m_axis[(int) p_axis]);
}

//Updates the state of all joysticks
void InputManager::updateJoysticks(){
    sf::Joystick::update();
}

//Assing input device to player
void InputManager::assignDevice(int p_device, int p_player){
    //Only change device of player 2 for now
    if (p_player == 1){
        m_inputDevices[p_player] = p_device;
        //std::cout << "Player " << p_player << ": Device " << m_inputDevices[p_player] << std::endl;
    }
}

//Updates joysticks state and booleans for each action
void InputManager::updateInputs(int p_player){
    int t_inputDevice = m_inputDevices[p_player];
    bool t_up, t_down; //They're not actions, but needed for some conditions


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

        t_up = 
            isKeyPressed(Key::W) ||
            isKeyPressed(Key::Up);
        t_down =
            isKeyPressed(Key::S) ||
            isKeyPressed(Key::Down);
        m_actions[p_player][(int) Action::Left] =
            isKeyPressed(Key::A) ||
            isKeyPressed(Key::Left);
        m_actions[p_player][(int) Action::Right] =
            isKeyPressed(Key::D) ||
            isKeyPressed(Key::Right);

        m_actions[p_player][(int) Action::Jump] =
            isKeyPressed(Key::Space);
        m_actions[p_player][(int) Action::Run] =
            isKeyPressed(Key::LShift) ||
            isKeyPressed(Key::RShift);
        m_actions[p_player][(int) Action::Block] =
            isKeyPressed(Key::B);
        m_actions[p_player][(int) Action::Pick] =
            isKeyPressed(Key::Q);      

        m_actions[p_player][(int) Action::SpecialAttackUp] =
            isKeyPressed(Key::X) &&
                t_up;
        m_actions[p_player][(int) Action::SpecialAttackDown] =
            isKeyPressed(Key::X) &&
                t_down;
        m_actions[p_player][(int) Action::SpecialAttackSide] =
            isKeyPressed(Key::X) &&
                (m_actions[p_player][(int) Action::Left] ||
                m_actions[p_player][(int) Action::Right]);
        m_actions[p_player][(int) Action::UltimateAttack] =
            isKeyPressed(Key::Z);
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

        t_up =
            getAxisPosition(t_inputDevice, Axis::Y) <= -75 ||
            getAxisPosition(t_inputDevice, Axis::PovY) == -100;
        t_down =
            getAxisPosition(t_inputDevice, Axis::Y) >= 75 ||
            getAxisPosition(t_inputDevice, Axis::PovY) == 100;
        m_actions[p_player][(int) Action::Left] =
            getAxisPosition(t_inputDevice, Axis::X) <= -75 ||
            getAxisPosition(t_inputDevice, Axis::PovX) == -100;
        m_actions[p_player][(int) Action::Right] =
            getAxisPosition(t_inputDevice, Axis::X) >= 75 ||
            getAxisPosition(t_inputDevice, Axis::PovX) == 100;

        m_actions[p_player][(int) Action::Jump] =
            isButtonPressed(t_inputDevice, Button::A);
        m_actions[p_player][(int) Action::Run] =
            isButtonPressed(t_inputDevice, Button::RB);
        m_actions[p_player][(int) Action::Block] =
            isButtonPressed(t_inputDevice, Button::LB);
        m_actions[p_player][(int) Action::Pick] =
            isButtonPressed(t_inputDevice, Button::Y);

        m_actions[p_player][(int) Action::SpecialAttackUp] =
            isButtonPressed(t_inputDevice, Button::B) &&
                t_up;
        m_actions[p_player][(int) Action::SpecialAttackDown] =
            isButtonPressed(t_inputDevice, Button::B) &&
                t_down;
        m_actions[p_player][(int) Action::SpecialAttackSide] =
            isButtonPressed(t_inputDevice, Button::B) &&
                (m_actions[p_player][(int) Action::Left] ||
                m_actions[p_player][(int) Action::Right]);
        m_actions[p_player][(int) Action::UltimateAttack] =
            getAxisPosition(t_inputDevice, Axis::Z) >= 0 &&
                getAxisPosition(t_inputDevice, Axis::R) >= 0;
    }

    //NPC
    else{
        for (int i = 0; i < (int) Action::Count; i++){
            m_actions[p_player][i] = false;
        }
    }
}

//Enables or disables inputs when key is pressed or released
void InputManager::updateKeyInputs(int p_key, bool p_enableMode){
//    int t_keyboardPlayer = getKeyboardPlayer();
//    std::cout << t_keyboardPlayer << std::endl;
//
//    if (t_keyboardPlayer != -1){
//        switch (p_key){
//            /*********************************** COMMON INPUTS ***********************************/
//            //Up input
//            case Key_Up:
//            case Key_W:{
//                m_upInput[t_keyboardPlayer] = p_enableMode;
//                break;
//            }
//
//            //Down input
//            case Key_Down:
//            case Key_S:{
//                m_downInput[t_keyboardPlayer] = p_enableMode;
//                break;
//            }
//
//            //Left input
//            case Key_Left:
//            case Key_A:{
//                m_leftInput[t_keyboardPlayer] = p_enableMode;
//                break;
//            }
//
//            //Right input
//            case Key_Right:
//            case Key_D:{
//                m_rightInput[t_keyboardPlayer] = p_enableMode;
//                break;
//            }
//            /*********************************** MENU ACTIONS ***********************************/
//
//
//            /*********************************** PLAYER ACTIONS ***********************************/
//            //Jump input
//            case Key_Space:{
//                m_jumpInput[t_keyboardPlayer] = p_enableMode;
//                break;
//            }
//
//            //Run input
//            case Key_LShift:
//            case Key_RShift:{
//                m_runInput[t_keyboardPlayer] = p_enableMode;
//                break;
//            }
//
//            //Block input
//            case Key_B:{
//                m_blockInput[t_keyboardPlayer] = p_enableMode;
//                break;
//            }
//
//            //Pick input
//            case Key_Q:{
//                m_pickInput[t_keyboardPlayer] = p_enableMode;
//                break;
//            }
//
//            /*********************************** ATTACKS ***********************************/
//            //Basic Attack
//            case Key_E:{
//                m_basicAttackInput[t_keyboardPlayer] = p_enableMode;
//                break;
//            }
//            
//            //Special Attacks
//            case Key_X:{
//                //Special Attack up
//                if (m_upInput[t_keyboardPlayer]){
//                    m_specialAttackUpInput[t_keyboardPlayer] = p_enableMode;
//                }
//                
//                //Special Attack Down
//                else if (m_downInput[t_keyboardPlayer]){
//                    m_specialAttackDownInput[t_keyboardPlayer] = p_enableMode;
//                }
//                
//                //Special Attack Side
//                else if (m_leftInput[t_keyboardPlayer] || m_rightInput[t_keyboardPlayer]){
//                    m_specialAttackSideInput[t_keyboardPlayer] = p_enableMode;
//                }
//                break;
//            }
//
//            //Ultimate Attack
//            case Key_Z:{
//                m_ultimateAttackInput[t_keyboardPlayer] = p_enableMode;
//                break;
//            }
//        }
//    }
//    
}

//Enables or disables inputs when button is pressed
void InputManager::updateButtonInputs(int p_player, int p_button, bool p_enableMode){

}

//Enables or disables inputs when axis is moved
void InputManager::updateAxisInputs(int p_player, int p_axis, bool p_enableMode){

}


//Returns true if the asked action's input is enabled
bool InputManager::checkInput(Action p_action, int p_player){
    return m_actions[p_player][(int) p_action];
}

//Returns the index of the player playing with keyboard, or -1 if nobody is using it
int InputManager::getKeyboardPlayer(){
    for(int i = 0; i < 4; i++){
        if(m_inputDevices[i] == -1){
            return i;
        }
    }

    return -1;
}