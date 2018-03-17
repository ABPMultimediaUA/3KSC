/********************************************************************************
*********************************************************************************
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
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    You can contact Chaotic Games at: chaoticgamesdev@gmail.com
*********************************************************************************
*********************************************************************************/

#include "../include/entities/Arena.hpp"
#include "../include/managers/EngineManager.hpp"
#include "../include/managers/PhysicsManager.hpp"

#include "../include/entities/characters/Kira.hpp"
#include "../include/entities/characters/Luka.hpp"
#include "../include/entities/characters/MiyagiMurasaki.hpp"
#include "../include/entities/characters/Plup.hpp"
#include "../include/entities/characters/Rawr.hpp"
#include "../include/entities/characters/Sparky.hpp"

#include "../include/entities/items/Item.hpp"
#include "../include/entities/items/LifeTank.hpp"
#include "../include/entities/items/Shield.hpp"
#include "../include/entities/items/Wings.hpp"
#include "../include/entities/items/FOAH.hpp"
#include "../include/entities/items/Portal.hpp"

#include "../include/debug.hpp"
#include "Client.hpp"
#include <iostream>

//Static members
const char* Arena::m_modelURLs[3] = {"assets/models/arenas/fusfus_stadium.obj", "assets/models/arenas/Lago_sakura.obj", "assets/models/arenas/fabrica_kawaiisaki.obj"};
const char* Arena::m_skyboxURLs[3][6] = {
    {"assets/skyboxes/fusfus_skybox/cloudtop_up.tga", "assets/skyboxes/fusfus_skybox/cloudtop_dn.tga", "assets/skyboxes/fusfus_skybox/cloudtop_lt.tga", "assets/skyboxes/fusfus_skybox/cloudtop_rf.tga", "assets/skyboxes/fusfus_skybox/cloudtop_ft.tga", "assets/skyboxes/fusfus_skybox/cloudtop_bk.tga"},
    {"assets/skyboxes/sakura_skybox/sep_up.tga", "assets/skyboxes/sakura_skybox/sep_dn.tga", "assets/skyboxes/sakura_skybox/sep_lt.tga", "assets/skyboxes/sakura_skybox/sep_rf.tga", "assets/skyboxes/sakura_skybox/sep_ft.tga", "assets/skyboxes/sakura_skybox/sep_bk.tga"},
    {"assets/skyboxes/sakura_skybox/sep_up.tga", "assets/skyboxes/sakura_skybox/sep_dn.tga", "assets/skyboxes/sakura_skybox/sep_lt.tga", "assets/skyboxes/sakura_skybox/sep_rf.tga", "assets/skyboxes/sakura_skybox/sep_ft.tga", "assets/skyboxes/sakura_skybox/sep_bk.tga"}
    };

EngineManager*  Arena::m_engineManager     = &EngineManager::instance();
PhysicsManager* Arena::m_physicsManager    = &PhysicsManager::instance();


//Instance initialization
Arena* Arena::m_instance = 0;

Arena::Arena(float p_position[3], float p_scale[3], int p_arenaIndex, bool p_debugMode):Entity(p_position, p_scale, m_modelURLs[p_arenaIndex], 1, p_arenaIndex){

    m_maxItems      = 500; //cambiar esto
    m_currentItems  = 0;
    m_items         = new Item*[m_maxItems];
    m_instance      = this;
    m_debugMode     = p_debugMode;
    m_spawningTime  = 10;
    m_clock         = new sf::Clock();
    m_playerCount   = 0;
    m_players       = new Character*[4];
    m_spawnedItems  = 0;
    m_usedItems     = 0;
    setSpawnPositions();
    setSkybox(p_arenaIndex);

}

Arena::~Arena(){}

Arena* Arena::getInstance(){
    return m_instance;
}

void Arena::spawnPlayers(){
    float positionRawr[3] = {-120, 20, 0};
    float positionPlup[3] = {120, 20, 0};

    m_players[m_playerCount++] = new Rawr("Player 1", positionRawr, false);
    m_players[m_playerCount++] = new Plup("Player 2", positionPlup, false);

    if(m_debugMode){
        for(int i = 0; i < m_playerCount; i++){
            m_players[i]->modeDebug();
        }
        modeDebug();
    }
}

void Arena::addPlayer(){
    float positionRawr[3] = {0, 100, 0};
    m_players[m_playerCount++] = new Rawr("Player 1", positionRawr, m_debugMode);
}

//Returns number of players
int Arena::getPlayerCount(){
    return m_playerCount;
}

//Returns the player with the given index
Character* Arena::getPlayer(int p_index){
    return m_players[p_index];
}


void Arena::spawnItems(){
   /* float positionItem[3] = {-100, 10, 0};
    
    m_items[m_currentItems++] = new Item(0, positionItem);
    positionItem[0] = -80;
    m_items[m_currentItems++] = new Item(0, positionItem);
    positionItem[0] = 80;
    m_items[m_currentItems++] = new Item(0, positionItem);
    positionItem[0] = 100;
    m_items[m_currentItems++] = new Item(0, positionItem);
    positionItem[0] = -60;
    m_items[m_currentItems++] = new Item(1, positionItem);
    positionItem[0] = 60;
    m_items[m_currentItems++] = new Item(1, positionItem);
    positionItem[0] = -30;
    m_items[m_currentItems++] = new Item(2, positionItem);
    positionItem[0] = 30;
    m_items[m_currentItems++] = new Item(2, positionItem);*/
    
}

//Checks if any of the items in the screen is where the player wants to pick it and uses it
void Arena::catchItem(int p_owner, float p_where[3]){    
    //Check if there's an item here and use it
    for (int i = 0; i < m_currentItems; i++){
        //Check not null
        if (m_items[i]){
            //X axis
            if(p_where[0] >= m_items[i]->getX() - 5 && p_where[0] <= m_items[i]->getX() + 5){
                //Y axis
                if(p_where[1] >= m_items[i]->getY() - 10 && p_where[1] <= m_items[i]->getY() + 10){
                    //Use the item
                    m_items[i]->setOwner(p_owner);
                    m_items[i]->use();

                    delete m_items[i];
                    m_items[i] = 0;
                    ++m_usedItems;
                    break;
                }
            }
        }
    }
}

void Arena::finishRound(){

}

void Arena::movePlatforms(){

}

void Arena::animateBackground(){

}

void Arena::restart(){
    
}

void Arena::modeDebug(){
    if(m_debugMode)
        m_debugBattlefield = new Debug(666, m_physicsManager->getBody(getId()));
}

void Arena::setSpawnPositions(){
   //m_spawnPosition[1] = {10, 100, 0};
   //m_spawnPosition[2] = {-50, 100, 0};
   //m_spawnPosition[0] = [-10, 100, 0};
   //m_spawnPosition[3] = {50, 100, 0};
}

void Arena::respawnPlayer(int p_player){
    //int randNum = rand()%(m_spawnPosition.length());
    float t_center[3] = {0, 170, 0};
    m_players[p_player]->respawn(t_center);
}

void Arena::update(){
    float t_time = m_clock->getElapsedTime().asSeconds();
    
    if(t_time > m_spawningTime)
    {
        m_clock->restart();
        spawnRandomItem();
    }
    if(m_debugMode)
        m_debugBattlefield->update();
}

bool Arena::spawnRandomItem(){
    if(m_spawnedItems - m_usedItems >= m_maxItemsOnScreen)
        return false;
    ++m_spawnedItems;
    float positionItem[3] = {-100, 10, 0};
    positionItem[0] = rand()%(120);
    if(positionItem[0]< 60)
        positionItem[1] = 54;
    else
        positionItem[1] = 10;

    if(rand()%2 == 0)
        positionItem[0] = positionItem[0] * (-1);

    //Type
    int t_type = rand()%3;
    spawnItemAt(rand()%3, positionItem[0], positionItem[1]);
    return true;
}

void Arena::setSkybox(int p_arenaIndex){
    m_engineManager->loadSkybox(m_skyboxURLs[p_arenaIndex]);
}

void Arena::onlineUpdate(){
    float t_time = m_clock->getElapsedTime().asSeconds();
    if(t_time > m_spawningTime)
    {
        m_clock->restart();
        if(spawnRandomItem()){
            Client::instance().spawnItem(m_lastItemType, m_items[m_currentItems]->getX(), m_items[m_currentItems]->getY());
        }
    }
    if(m_debugMode)
        m_debugBattlefield->update();
}

void Arena::spawnItemAt(int p_type, int x, int y)
{
    float t_position[3] = {x, y, 0};
    switch (p_type){
        case 0:     { m_items[m_currentItems] = new LifeTank(t_position);   }   break;
        case 1:     { m_items[m_currentItems] = new Shield(t_position);     }   break;
        case 2:     { m_items[m_currentItems] = new Wings(t_position);      }   break;
    }

    m_currentItems++;
    m_lastItemType = p_type;
}

void Arena::setOnline(bool p_state)
{
    m_online = p_state;
}

bool Arena::getOnline()
{
    return m_online;
}