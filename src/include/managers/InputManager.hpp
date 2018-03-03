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

#ifndef INPUT_MANAGER
#define INPUT_MANAGER

//#include "../entities/characters/Character.hpp"
#include "../extra/Actions.hpp"
#include "../extra/Inputs.hpp"
#include <SFML/Window/Keyboard.hpp>//DELETE!!!
#include <SFML/Window/Joystick.hpp>//DELETE!!!
#include <SFML/Window/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <Client.hpp>

class InputManager{
    public:
        static InputManager& instance();
        InputManager();
        ~InputManager();
        bool    eventHandler();
        void    onKeyPressed(int p_key);
        bool    isKeyPressed(Key p_key);
        bool    isConnected(int p_joystick);
        bool    isButtonPressed(int p_joystick, Button p_button);
        float   getAxisPosition(int p_joystick, Axis p_axis);
        void    updateJoysticks();
        void    assignDevice(int p_device, int p_player);
        void    onlineMode();
        void    setOnlineControl(int p_player);
        void    setNetPlayer(int p_player);        
        void    updateInputs(int p_player);
        bool    checkInput(Action p_action, int p_player);
        int     getInputDevice(int p_player);
    
    private:
        int**                   m_bindings;   
        sf::Keyboard::Key       m_keys[101];
        sf::Joystick::Axis      m_axis[8];
        Client*                 m_client;
        //Event handling
        sf::Window*             m_window;             
        sf::Event*              m_event;

        bool m_isOnline = false;
        //Input device for each player [0-3]: Joysticks, -1: Keyboard, -2: NPC
        int     m_inputDevices[4];

        //Conditions for each Input (they change depending on keyboard/joystick control)
        //Input booleans
        bool m_actions[4][(int) Action::Count];
};

#endif