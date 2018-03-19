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
#include "../include/extra/Inputs.hpp"
#include "../include/extra/Actions.hpp"
#include <iostream> // to write in console
#include <cstring> //For std::memcpy()

//Returns the only instance of this class
InputManager& InputManager::instance(){
    static InputManager instance;
    return instance;
}

//Constructor
InputManager::InputManager(){
    m_engineManager = &EngineManager::instance();

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
    m_inputDevices[0]   = -2;
    m_inputDevices[1]   = -1;
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
        }
    }

    return t_eventReceived;
}

//Specific Key press handler
void InputManager::onKeyPressed(int p_key){

}

//Returns whether key with code p_key is pressed or not
bool InputManager::isKeyPressed(Key p_key){
    bool t_result = sf::Keyboard::isKeyPressed(m_keys[(int) p_key]);
    return t_result;
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
    // if (p_player == 1){
    //     m_inputDevices[p_player] = p_device;
    //     std::cout << "Player " << p_player << ": Device " << m_inputDevices[p_player] << std::endl;
    // }
    //COMENTADO PARA EL ONLINE
}

void InputManager::onlineMode(){
    m_client = &Client::instance();
    m_isOnline = true;
    for (int i = 0; i < sizeof(m_inputDevices) / sizeof(int); ++i)
        m_inputDevices[i] = -3; //Unassign devices so server assigns one
}

void InputManager::setOnlineControl(int p_player){
    m_inputDevices[p_player] = -1;
}

void InputManager::setNetPlayer(int p_player, bool p_actions[12]){
    m_actions[p_player][(int) Action::Left]                 = p_actions[0]; 
    m_actions[p_player][(int) Action::Right]                = p_actions[1];             
    m_actions[p_player][(int) Action::Jump]                 = p_actions[2];
    m_actions[p_player][(int) Action::Run]                  = p_actions[3];
    m_actions[p_player][(int) Action::Block]                = p_actions[4];
    m_actions[p_player][(int) Action::Pick]                 = p_actions[5];
    m_actions[p_player][(int) Action::BasicAttack]          = p_actions[6];
    m_actions[p_player][(int) Action::SpecialAttackUp]      = p_actions[7];
    m_actions[p_player][(int) Action::SpecialAttackDown]    = p_actions[8];
    m_actions[p_player][(int) Action::SpecialAttackSide]    = p_actions[9];
    m_actions[p_player][(int) Action::UltimateAttack]       = p_actions[10];
}

// Enables an action for AI
void InputManager::setAction(Action p_action, int p_player, bool p_bool){
    m_actions[p_player][(int)p_action] = p_bool;
}

//Updates joysticks state and booleans for each action
void InputManager::updateActions(int p_player){
    int t_inputDevice = m_inputDevices[p_player];
    bool t_up, t_down; //They're not actions, but needed for some conditions
    //Keyboard input
    if (t_inputDevice == -1){
        if(!m_engineManager->getDevice()->isWindowActive()) return;
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

        m_actions[p_player][(int) Action::BasicAttack] =
            isKeyPressed(Key::E);
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
    else if (t_inputDevice == -3)
    {
        //online player
    }
    //Joystick input
    else if (t_inputDevice != -2){
        if(!m_engineManager->getDevice()->isWindowActive()) return;
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

        m_actions[p_player][(int) Action::BasicAttack] =
            isButtonPressed(t_inputDevice, Button::X);
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
            //m_actions[p_player][i] = false;
        }
    }

    if(m_isOnline && p_player == m_client->getPlayer())
        updateOnlineInput(p_player);
}

//Returns true if the asked action's input is enabled
bool InputManager::checkAction(Action p_action, int p_player){
    return m_actions[p_player][(int) p_action];
}

//Returns the input device for the specified player
int InputManager::getInputDevice(int p_player){
    return m_inputDevices[p_player];
}

void InputManager::updateOnlineInput(int p_player){
    bool t_actions[12];
    bool t_flag = false;
    uint i;
    for(i = 0; i < 12; i++)
    {
        if(m_actions[p_player][i])
            t_actions[i] = true;
        else
            t_actions[i] = false;

        if(t_actions[i] != m_lastActions[i])
        {
            m_lastActions[i] = t_actions[i];
            t_flag = true;
        }
    }
    if(t_flag)
        sendOnlineInput();
}

void InputManager::sendOnlineInput(){
    m_client->sendAction(m_lastActions);
}