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

#include "../include/entities/characters/Plup.hpp"
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

EngineManager*  Arena::m_engineManager     = &EngineManager::instance();
PhysicsManager* Arena::m_physicsManager    = &PhysicsManager::instance();


//Instance initialization
Arena* Arena::m_instance = 0;

Arena::Arena(float p_position[3], float p_scale, const char* p_modelURL, bool p_debugMode):Entity(p_position, p_scale, p_modelURL, 1){

    m_currentItems  = 0;
    //m_items         = new Item*[m_maxItemsOnScreen];
    m_instance      = this;
    m_debugMode     = p_debugMode;
    m_spawningTime  = 10;
    m_clock         = new sf::Clock();
    m_playerCount   = 0;
    m_players       = new Character*[4];
    m_usedItems     = 0;
    //setSpawnPositions();
}

Arena::~Arena(){}

Arena* Arena::getInstance(){
    return m_instance;
}

void Arena::spawnPlayers(){
    float positionPortal[3] = {-70, 5, 0};
    //new Portal(positionPortal);

    m_players[m_playerCount++] = new Sparky("Player 1", m_spawnPositions[0], false);
    m_players[m_playerCount++] = new Plup("Player 2", m_spawnPositions[1], false);
    //m_players[m_playerCount++] = new Plup("Player 3", m_spawnPositions[2], false);

    if(m_debugMode){
        for(int i = 0; i < m_playerCount; i++){
            m_players[i]->modeDebug();
        }
        modeDebug();
    }
}

void Arena::addPlayer(){
    float positionSparky[3] = {0, 100, 0};
    m_players[m_playerCount++] = new Sparky("Player 1", positionSparky, m_debugMode);
}

//Returns number of players
int Arena::getPlayerCount(){
    return m_playerCount;
}

//Returns the player with the given index
Character* Arena::getPlayer(int p_index){
    return m_players[p_index];
}

//Checks if any of the items in the screen is where the player wants to pick it and uses it
void Arena::catchItem(int p_owner, float p_where[3]){    
    //Check if there's an item here and use it
    for (int i = 0; i < m_items.size(); i++){
        //X axis
        if(p_where[0] >= m_items.at(i)->getX() - 5 && p_where[0] <= m_items.at(i)->getX() + 5){
            //Y axis
            if(p_where[1] >= m_items.at(i)->getY() - 10 && p_where[1] <= m_items.at(i)->getY() + 10){
                //Use the item
                m_items.at(i)->setOwner(p_owner);
                m_items.at(i)->use();

                delete m_items.at(i);
                m_items.at(i) = 0;
                m_items.erase(m_items.begin()+i);
                ++m_usedItems;
                break;
            }
        }
    }
}

void Arena::finishRound(){}

void Arena::movePlatforms(){}

void Arena::animateBackground(){}

void Arena::restart(){}

void Arena::modeDebug(){
    if(m_debugMode)
        m_debugBattlefield = new Debug(666, m_physicsManager->getBody(getId()));
}

void Arena::setSpawnPositions(float p_spawnPositions[4][3]){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 3; j++){
            m_spawnPositions[i][j] = p_spawnPositions[i][j];
        }
    }
}

void Arena::respawnPlayer(int p_player){
    m_players[p_player]->respawn(m_respawnPosition);
}

void Arena::update(){
    float t_time = m_clock->getElapsedTime().asSeconds();
    
    if(t_time > m_spawningTime){
        m_clock->restart();
        spawnRandomItem();
    }

    for(int i = 0; i < m_items.size(); i++){
        if(m_items.at(i)->update())
            m_items.erase(m_items.begin()+i);
    }

    if(m_debugMode)
        m_debugBattlefield->update();
}

bool Arena::spawnRandomItem(){
    if(m_items.size() >= m_maxItemsOnScreen)
        return false;

    int range = m_spawnItemRange[1] - m_spawnItemRange[0] + 1;
    int randx = m_spawnItemRange[0] + (rand() % range);

    spawnItemAt(rand()%3, randx, m_spawnItemRange[2]);
    return true;
}

void Arena::onlineUpdate(){
    float t_time = m_clock->getElapsedTime().asSeconds();
    
    if(t_time > m_spawningTime){
        m_clock->restart();
        if(spawnRandomItem()){
            Client::instance().spawnItem(m_lastItemType, m_items.at(m_currentItems)->getX(), m_items.at(m_currentItems)->getY());
        }
    }
    if(m_debugMode)
        m_debugBattlefield->update();
}

void Arena::spawnItemAt(int p_type, int x, int y){
    float t_position[3] = {x, y, 0};

    switch (p_type){
        case 0:     { m_items.push_back(new LifeTank(t_position));   }   break;
        case 1:     { m_items.push_back(new Shield(t_position));     }   break;
        case 2:     { m_items.push_back(new Wings(t_position));      }   break;
    }

    m_currentItems = m_items.size();
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