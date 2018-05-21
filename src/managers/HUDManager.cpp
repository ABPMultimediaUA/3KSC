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

#include "../include/managers/HUDManager.hpp"
#include "../include/Game.hpp"
#include "../include/managers/EngineManager.hpp"
#include "../include/ChaoticEngine/fachada/CESceneSprite.hpp"
#include <string> //For std::to_string()
#include <iostream>

/* ****************************** PLAYER HUD ****************************** */
//Destructor
PlayerHUD::~PlayerHUD(){
    if  (face   )   { delete face;      face = nullptr;     }
    if  (bg     )   { delete bg;        bg = nullptr;       }
    if  (hp     )   { delete hp;        hp = nullptr;       }
    if  (mp     )   { delete mp;        mp = nullptr;       }
    if  (up     )   { delete up;        up = nullptr;       }
    if  (lives  )   { delete lives;     lives = nullptr;    }
}










/* ****************************** HUD MANAGER ****************************** */
//Returns the only instance of this class
HUDManager& HUDManager::instance(){
    static HUDManager instance;
    return instance;
}

//Constructor
HUDManager::HUDManager(){
    m_game              = Game::getInstance();
    m_engineManager     = &EngineManager::instance();
    
    initializePlayer(0);
    initializePlayer(1);
}

//Destructor
HUDManager::~HUDManager(){
    for (int i = 0; i < 2; i++){
        if (m_playerHUDs[i])    { delete m_playerHUDs[i];   m_playerHUDs[i] = nullptr;  }
    }
}

void HUDManager::initializePlayer(int p_index){
    PlayerHUD* t_playerHUD = new PlayerHUD();

    //Data getting
    bool t_NPC      = m_game->isNPC(p_index);
    int t_chosen    = m_game->getChosenPlayer(p_index);
    int t_lives     = m_game->getLives();    
    
    std::cout << "Lives: " << t_lives << std::endl;

    //Faces
    std::string t_string1 = "assets/UI/HUD/Faces/";
    std::string t_string2 = "assets/UI/HUD/Faces/";
    std::string t_name;
    std::string t_type;

    switch (t_chosen){
        case 0: { t_name = "PLUP";      break;  }
        case 1: { t_name = "SPARKY";    break;  }
    }

    if (t_NPC){

        t_type = "_AI_";
    }
    else{
        switch (p_index){
            case 0: { t_type = "_P1_";   break;  }
            case 1: { t_type = "_P2_";   break;  }
        }
    }

    t_string1 += t_name + t_type + "OK.png";
    t_string2 += t_name + t_type + "HURT.png";

    const char* t_url1 = t_string1.c_str();
    const char* t_url2 = t_string2.c_str();

    t_playerHUD->face = m_engineManager->createSprite(t_url1, 128, 192, false);
    t_playerHUD->face->addTexture(t_url2);

    //Bars
    t_playerHUD->bg  = m_engineManager->createSprite("assets/UI/HUD/Bars/BG.png" , 300   , 128   , false);
    t_playerHUD->hp  = m_engineManager->createSprite("assets/UI/HUD/Bars/HP.png" , 300   , 128   , false);
    t_playerHUD->mp  = m_engineManager->createSprite("assets/UI/HUD/Bars/MP.png" , 300   , 128   , false);
    t_playerHUD->up  = m_engineManager->createSprite("assets/UI/HUD/Bars/UP.png" , 300   , 128   , false);
    t_playerHUD->hp->addTexture("assets/UI/HUD/Bars/HP_LOW.png");

    //Lives
    t_playerHUD->lives = m_engineManager->createSprite("assets/UI/HUD/Lives/0.png"   , 300,  64   , false);
    t_playerHUD->lives->addTexture("assets/UI/HUD/Lives/1.png");
    t_playerHUD->lives->addTexture("assets/UI/HUD/Lives/2.png");
    t_playerHUD->lives->addTexture("assets/UI/HUD/Lives/3.png");
    t_playerHUD->lives->addTexture("assets/UI/HUD/Lives/4.png");
    t_playerHUD->lives->addTexture("assets/UI/HUD/Lives/5.png");
    t_playerHUD->lives->addTexture("assets/UI/HUD/Lives/6.png");
    t_playerHUD->lives->setTexture(t_lives);

    //Placing
    int t_x = -482 + (536 * p_index);
    // int t_y = -290;
    int t_y = 356;

    t_playerHUD->face->setAbsolutePosition(t_x, t_y, 1);
    t_playerHUD->bg->setAbsolutePosition(t_x + 128, t_y, 1);
    t_playerHUD->hp->setAbsolutePosition(t_x + 128, t_y, 2);
    t_playerHUD->mp->setAbsolutePosition(t_x + 128, t_y, 3);
    t_playerHUD->up->setAbsolutePosition(t_x + 128, t_y, 4);
    t_playerHUD->lives->setAbsolutePosition(t_x + 128, t_y - 128, 1);

    m_playerHUDs[p_index] = t_playerHUD;
}

//Changes the HP of a player in the screen
void HUDManager::setHP(int p_player, int p_HP){
    // TODO: Change size and color
}

//Changes the MP of a player in the screen
void HUDManager::setMP(int p_player, int p_MP){
    // TODO: Change size
}

//Changes the lives left of a player in the screen
void HUDManager::setLives(int p_player, int p_lives){
    //TODO: Change lives texture
}

//Updates the UI
void HUDManager::update(){
    
}

//Displays the UI
void HUDManager::render(){

}