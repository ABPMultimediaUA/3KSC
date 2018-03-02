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

#ifndef IN_GAME_STATE
#define IN_GAME_STATE

class Game;
class EngineManager;
class InputManager;
class UIManager;
class SoundManager;
class PhysicsManager;
class AIManager;
class Client;
class Arena;

#include "State.hpp"

class InGameState : public State{
    private:
        Game*           m_game;
        EngineManager*  m_engineManager;
        InputManager*   m_inputManager;
        UIManager*      m_UIManager;
        SoundManager*   m_soundManager;
        PhysicsManager* m_physicManager;
        AIManager*      m_AIManager;
        Client*         m_client;
        Arena*          m_arena;

        bool            m_onlineMode;
    public:
        InGameState(Game* p_game);
        ~InGameState();
        void    input();
        void    update();
        void    render();
        void    nextState();
};

#endif