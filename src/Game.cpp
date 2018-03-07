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

#include "include/Game.hpp"
#include "include/states/State.hpp"
#include "include/states/InGameState.hpp"
#include "include/managers/EngineManager.hpp"

#include <iostream>
#include <stdio.h>

//Constructor
Game::Game(){
    m_engineManager = &EngineManager::instance();

    if (m_engineManager->createWindow(false)){
        m_state = new InGameState(this, false);
    }
}

//Destructor
Game::~Game(){
    delete m_state;
    delete m_engineManager;
}

//Changes to an specified state
void Game::setState(State* p_state){
    delete m_state;
    m_state = p_state;
}

//Changes to the next stage
void Game::nextState(){
    m_state->nextState();
}

//Main loop of the game
void Game::run(){
    while (m_engineManager->running()){
        m_state->input();
        m_state->update();
        m_state->render();
    }

    m_engineManager->stop();
}