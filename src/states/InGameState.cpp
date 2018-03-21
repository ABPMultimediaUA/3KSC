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
#include "../include/Game.hpp"

#include "../include/managers/EngineManager.hpp"
#include "../include/managers/InputManager.hpp"
// #include "../include/managers/UIManager.hpp"
#include "../include/managers/SoundManager.hpp"
#include "../include/managers/PhysicsManager.hpp"
#include "../include/entities/Arena.hpp"

#include "../include/AI/AICharacter.hpp"
#include "../include/AI/AIKira.hpp"
#include "../include/AI/AILuka.hpp"
#include "../include/AI/AIMiyagi.hpp"
#include "../include/AI/AIPlup.hpp"
#include "../include/AI/AIRawr.hpp"
#include "../include/AI/AISparky.hpp"
#include "../include/AI/Pathfinding.hpp"

#include "../include/Client.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


//Constructor
InGameState::InGameState(Game* p_game, bool p_onlineMode){
    m_game              = p_game;
    m_engineManager     = &EngineManager::instance();
    m_inputManager      = &InputManager::instance();
    // m_UIManager         = &UIManager::instance();
    m_soundManager      = &SoundManager::instance();
    m_physicsManager    = &PhysicsManager::instance();
    m_pathfinding       = &Pathfinding::instance();

    readFileMapCgm("assets/Fusfus_Stadium.cgm");

    //Static members
    const char* m_skyboxURLs[6] = {"assets/skyboxes/fusfus_skybox/cloudtop_up.tga", "assets/skyboxes/fusfus_skybox/cloudtop_dn.tga", "assets/skyboxes/fusfus_skybox/cloudtop_lt.tga", "assets/skyboxes/fusfus_skybox/cloudtop_rf.tga", "assets/skyboxes/fusfus_skybox/cloudtop_ft.tga", "assets/skyboxes/fusfus_skybox/cloudtop_bk.tga"};
    
    //Create arena
    float t_position[3] = {0, -2, 10};
    //float t_scale[3] = {120, 0.5, 2};
    m_arena = new Arena(t_position, 10, "assets/models/arenas/fusfus_stadium.obj", false);
    m_engineManager->loadSkybox(m_skyboxURLs);

    //Online stuff
    m_onlineMode = p_onlineMode;
    // char t_onlinePrompt[5];
    // std::cout<<"Online mode? (Y)/(N)"<<std::endl;
    // std::cin >> t_onlinePrompt;

    // if (t_onlinePrompt[0] == 'y' || t_onlinePrompt[0] == 'Y'){
    if (m_onlineMode){
        m_client = &Client::instance();
        m_client->start();
        m_inputManager->onlineMode();
        m_onlineMode = true;
    }

    else{
       // m_arena->spawnItems();
        m_arena->spawnPlayers();
    }

    //Create camera
    float t_cameraPosition[3] = {0, 90, -150};
    float t_cameraTarget[3] = {0, 50, 0};
    m_engineManager->createCamera(t_cameraPosition, t_cameraTarget);
    
    // Play music
    m_soundManager->loadBank(SoundID::S_FOSFOS_STADIUM);
    //m_soundManager->loadEvents(SoundID::S_FOSFOS_STADIUM);
    m_soundManager->createSoundEvent("event:/music/fosfosStadium", "fos_music");
    m_soundManager->playSound("fos_music");

    
    //Initialize AI
    int i, t_playerCount = m_arena->getPlayerCount();
    Character* t_currentPlayer;
    m_AIPlayers = new AICharacter*[t_playerCount];
    m_pathfinding->testWaypoints();

    //Create AI instances for needed players and build trees
    for (i = 0; i < t_playerCount; i++){
        t_currentPlayer = m_arena->getPlayer(i);

        if(t_currentPlayer->isNPC()){
            //Create AI of specific type
            switch (t_currentPlayer->getType()){
                case 0:     m_AIPlayers[i] = new AIKira();      break;
                case 1:     m_AIPlayers[i] = new AILuka();      break;
                case 2:     m_AIPlayers[i] = new AIMiyagi();    break;
                case 3:     m_AIPlayers[i] = new AIPlup();      break;
                case 4:     m_AIPlayers[i] = new AIRawr();      break;
                case 5:     m_AIPlayers[i] = new AISparky();    break;
            }
            
            m_AIPlayers[i]->buildTree();
        }
        else{
            m_AIPlayers[i] = 0;
        }
    }

    m_engineManager->timeStamp();
}

//Destructor
InGameState::~InGameState(){
    delete m_game;
    delete m_engineManager;
    delete m_inputManager;
    // delete m_UIManager;
    delete m_soundManager;
    delete m_physicsManager;
    delete m_AIPlayers;
    delete m_client;
    delete m_arena;
}

void InGameState::input(){

}

void InGameState::update(){
    m_soundManager->update(false);
    m_engineManager->updateFrameDeltaTime();
    int t_playerCount = m_arena->getPlayerCount();
    int i;        

    //Update AIs
    for (i = 0; i < t_playerCount; i++){
        if (m_AIPlayers[i] != 0){
            m_AIPlayers[i]->update();
        }
    }

    if(m_onlineMode){
        m_client->update();
    }
    else
        m_arena->update();

    //Update the physics one step more(need to be done first of all)
    m_physicsManager->update();
    
    Character* t_currentPlayer;

    //Input and update for every character
    for (i = 0; i < t_playerCount; i++){
        t_currentPlayer = m_arena->getPlayer(i);

        // if(inputManager->eventHandler()){
        //    currentPlayer->input();
        // }
        
        t_currentPlayer->input();
        t_currentPlayer->update();
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

void InGameState::readFileMapCgm(const char* p_fileCgm){

    std::ifstream t_file(p_fileCgm);
    std::string t_line;
    std::string t_name;
    while(std::getline(t_file, t_line)){
        if(t_line == "" || t_line[0] == '#')// Skip everything and continue with the next line
            continue;

        std::istringstream t_lineStream(t_line);
        t_lineStream >> t_name;

        if(t_name == "m"){
            std::cout << "m" <<std::endl;
        }
        else if(t_name == "c"){
            std::cout << "c" <<std::endl;     
        }
        else if(t_name == "mu"){
            std::cout << "mu" <<std::endl;          
        }
    }

        /*if(t_name == "o"){
            if(m_totalVertex != 0){
                pushVertex(t_minX, t_maxX, t_minY, t_maxY, t_minZ, t_maxZ);

                t_maxX = -999.0, t_maxY = -999.0, t_maxZ = -999.0;
                t_minX =  999.0, t_minY =  999.0, t_minZ =  999.0;
            }
            m_totalVertex++;
        }

        if(t_name == "v"){// Vertex
            sscanf(t_line.c_str(), "%*s %f %f %f", &t_X, &t_Y, &t_Z);

            compareMaxAndMin(t_X, t_maxX, t_minX);
            compareMaxAndMin(t_Y, t_maxY, t_minY);
            compareMaxAndMin(t_Z, t_maxZ, t_minZ);
        }
    }
    pushVertex(t_minX, t_maxX, t_minY, t_maxY, t_minZ, t_maxZ);*/
}