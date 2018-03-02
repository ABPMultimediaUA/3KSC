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

#include "../include/states/InGameState.hpp"
#include "../include/states/EndGameState.hpp"
#include "../include/managers/EngineManager.hpp"
#include "../include/managers/InputManager.hpp"
#include "../include/managers/UIManager.hpp"
#include "../include/managers/SoundManager.hpp"
#include "../include/managers/PhysicsManager.hpp"
#include "../include/managers/AIManager.hpp"
#include "../include/Game.hpp"

//Constructor
InGameState::InGameState(Game* p_game) 
    : m_game(p_game){
    m_engineManager = &EngineManager::instance();
    m_inputManager  = &InputManager::instance();
    //m_UIManager     = &UIManager::instance();
    m_soundManager  = &SoundManager::instance();
    m_physicManager = &PhysicsManager::instance();
    m_AIManager     = &AIManager::instance();

    //Create arena
    float t_position[3] = {0, 1, 0};
    float t_scale[3] = {120, 0.5, 2};
    m_arena = new Arena(t_position, t_scale, 0, false);

    //Online stuff
    char t_onlinePrompt[5];
    m_onlineMode = false;
    std::cout<<"Online mode? (Y)/(N)"<<std::endl;
    std::cin >> t_onlinePrompt;

    if (t_onlinePrompt[0] == 'y' || t_onlinePrompt[0] == 'Y'){
        m_client = &Client::instance();
        m_client->start();
        m_inputManager->onlineMode();
        m_onlineMode = true;
    }

    else{
        m_arena->spawnItems();
        m_arena->spawnPlayers();
    }

    //Create camera
    float t_cameraPosition[3] = {0, 90, -150};
    float t_cameraTarget[3] = {0, 50, 0};
    m_engineManager->createCamera(t_cameraPosition, t_cameraTarget);
    
    // Play music
    m_soundManager->createSoundEvent("event:/Music/Music", "music");
    m_soundManager->playSound("music");
    
    // UIManager* uiManager = UIManager::instance();
    
    //Initialize AI
    m_AIManager->buildTree();

    m_engineManager->timeStamp();
}

//Destructor
InGameState::~InGameState(){
    delete m_game;
    delete m_engineManager;
    delete m_inputManager;
    delete m_UIManager;
    delete m_soundManager;
    delete m_physicManager;
    delete m_AIManager;
    delete m_client;
    delete m_arena;
}

void InGameState::input(){

}

void InGameState::update(){
    m_soundManager->update(false);
    m_engineManager->updateFrameDeltaTime();            
    m_AIManager->update();

    if(m_onlineMode){
        m_client->recive();
    }

    m_physicsManager->getWorld()->Step(physicsManager->getTimeStep(), physicsManager->getVelocityIterations(), physicsManager->getPositionIterations());
    
    int i, t_playerCount = m_arena->getPlayerCount();
    Character* t_currentPlayer;

    //Input and update for every character
    for (i = 0; i < t_playerCount; i++){
        t_currentPlayer = m_arena->getPlayer(i);

        // if(inputManager->eventHandler()){
        //    currentPlayer->input();
        // }
        
        t_currentPlayer->input();
        t_currentPlayer->update();
        m_arena->update();
    }
}

void InGameState::render(){
    m_engineManager->updateCamera();
    m_engineManager->drawScene();
    // m_UIManager->render();
}

//Change to next state
void InGameState::nextState(){
    m_game->setState(new EndGameState(m_game));
}