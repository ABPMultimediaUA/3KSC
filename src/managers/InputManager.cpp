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
#include <SFML/Window/Joystick.hpp>
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
}

//Destructor
InputManager::~InputManager(){}

//Specific Key press handler
void InputManager::onKeyPressed(int p_key){

}

//Returns true if key with code p_key is pressed, false otherwise
bool InputManager::isKeyPressed(int p_key){
    return sf::Keyboard::isKeyPressed(m_keys[p_key]);
}