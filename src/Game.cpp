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
#include "include/managers/EngineManager.hpp"
#include "include/managers/InputManager.hpp"
#include "include/states/InGameState.hpp"

#include <iostream>
#include <stdio.h>
#include <sys/time.h>
#include <chrono>

//Constructor
Game::Game(){
    m_engineManager = &EngineManager::instance();
    m_inputManager  = &InputManager::instance();
    
    const int FPS = 170;
    m_nanoFrames = 1000000000/FPS;
    
    m_engineManager->createWindow(false);
    m_state = new InGameState(this, false);
}

//Destructor
Game::~Game(){
    delete m_engineManager;
    m_engineManager = nullptr;

    delete m_inputManager;
    m_inputManager = nullptr;

    delete m_state;
    m_state = nullptr;
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
    auto t_now      = std::chrono::high_resolution_clock::now();
    auto t_elapsed  = std::chrono::high_resolution_clock::now() - t_now;

    while(true){
        if(!m_engineManager->running())
            break;

        t_elapsed = std::chrono::high_resolution_clock::now() - t_now;
        m_elapsedTotal += std::chrono::duration_cast<std::chrono::nanoseconds>(t_elapsed).count();

        while(m_elapsedTotal > m_nanoFrames){
            fixedUpdate(m_elapsedTotal);
            m_elapsedTotal  -= m_nanoFrames;
        }

        t_now = std::chrono::high_resolution_clock::now();
    }
}

void Game::fixedUpdate(long long p_delta){
    m_state->setDeltaTime(p_delta);
    m_state->input();
    m_state->update();
    m_state->render();
}