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
#include "../include/managers/InputManager.hpp"
#include "../include/managers/PhysicsManager.hpp"
#include "../include/managers/SoundManager.hpp"

#include "../include/entities/characters/Plup.hpp"
#include "../include/entities/characters/Sparky.hpp"

#include "../include/entities/items/Item.hpp"
#include "../include/entities/items/LifeTank.hpp"
#include "../include/entities/items/Shield.hpp"
#include "../include/entities/items/Wings.hpp"
#include "../include/entities/items/FOAH.hpp"

#include "Client.hpp"
#include <iostream>

//Instance initialization
Arena* Arena::m_instance = 0;

Arena::Arena(float p_position[3], float p_scale, const char* p_modelURL) : Entity(p_position, p_scale, p_modelURL, 1){
    m_currentItems      = 0;
    //m_items           = new Item*[m_maxItemsOnScreen];
    m_instance          = this;
    m_offsetSpawnTime   = 7.5;
    m_nextSpawnTime     = m_inputManager->getMasterClock() + m_offsetSpawnTime;
    m_playerCount       = 0;
    m_players           = new Character*[4];
    m_usedItems         = 0;

    m_portalDuration    = 0.75;
    m_portalOffsetTime  = 10;
    m_portalSpawnTime   = m_inputManager->getMasterClock() + m_portalOffsetTime;
    m_portalSpawned     = false;

    m_musicIntensity[0] = 0.8;
    m_musicIntensity[1] = 0.6;
    m_musicIntensity[2] = 0.4;
    m_musicIntensity[3] = 0.0;
}

Arena::~Arena(){
    for(int i = 0; i < m_playerCount; i++){
        delete m_players[i];
        m_players = nullptr;
    }

    delete[] m_players;
    m_players = nullptr;

    if(m_portal){
        delete m_portal;
        m_portal = nullptr;
    }
}

Arena* Arena::getInstance(){
    return m_instance;
}

void Arena::spawnPlayers(){
    m_players[m_playerCount++] = new Sparky("Player 1", m_spawnPositions[0]);
    //m_players[m_playerCount++] = new Plup("Player 2", m_spawnPositions[1]);
    //m_players[m_playerCount++] = new Plup("Player 3", m_spawnPositions[2]);
  //  m_engineManager->createParticleSystem("assets/fire.png", 50, 5, 5, 10, 2, -20, 20, false);
    std::cout << "PLAYER COUNT " << m_playerCount << std::endl;
    m_soundManager->modifyParameter("fos_music", m_musicIntensity[m_playerCount], "Intensity", false);
}

void Arena::addPlayer(bool p_bool){
    float positionSparky[3] = {0, 100, 0};
    m_players[m_playerCount++] = new Sparky("Player 1", positionSparky, p_bool);
}

//Returns number of players
int Arena::getPlayerCount(){
    return m_playerCount;
}

//Returns the player with the given index
Character* Arena::getPlayer(int p_index){
    if(m_players[p_index] != 0)
        return m_players[p_index];
    else
        return 0;
}

//Checks if any of the items in the screen is where the player wants to pick it and uses it
void Arena::catchItem(int p_owner, float p_where[3]){    
    //Check if there's an item here and use it
    for (int i = 0; i < m_items.size(); i++){
        //X axis
        if(p_where[0] >= m_items.at(i)->getX() - 1 && p_where[0] <= m_items.at(i)->getX() + 1){
            //Y axis
            if(p_where[1] >= m_items.at(i)->getY() - 1 && p_where[1] <= m_items.at(i)->getY() + 1){
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

void Arena::setSpawnPositions(float p_spawnPositions[4][3]){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 3; j++){
            m_spawnPositions[i][j] = p_spawnPositions[i][j];
        }
    }
}

float* Arena::getRespawnPosition(){
    return m_respawnPosition;
}

void Arena::update(float p_delta){
    float t_time = m_inputManager->getMasterClock();
    
    if(t_time > m_nextSpawnTime){
        m_nextSpawnTime = t_time + m_offsetSpawnTime;
        spawnRandomItem();
    }

    for(int i = 0; i < m_items.size(); i++){
        if(m_items.at(i)->update())
            m_items.erase(m_items.begin()+i);
    }

    if(!m_soundManager->isPlaying("fos_ambient"))
        m_soundManager->playSound("fos_ambient");
    if(m_portalSpawned)
        m_portal->update(p_delta);
    m_engineManager->updateParticleSystem();
    portalSpawner();
}

void Arena::portalSpawner(){
    float t_time = m_inputManager->getMasterClock();

    if(!m_portalSpawned && t_time > m_portalSpawnTime){
        spawnPortal();
    }
}

bool Arena::spawnRandomItem(){
    if(m_items.size() >= m_maxItemsOnScreen)
        return false;

    int range = m_spawnItemRange[1] - m_spawnItemRange[0] + 1;
    int randx = m_spawnItemRange[0] + (rand() % range);
    int random = rand()%(3-0 + 1) + 0;
    spawnItemAt(random, randx, m_spawnItemRange[2]);
    return true;
}

void Arena::spawnPortal(){
    std::cout<<"portal spawned"<<std::endl;
    float positionPortal[3] = {0, 0.5, 0};
    m_portal = new Portal(positionPortal);
    m_portalSpawned = true;
}

void Arena::hidePortal(){
    m_portalSpawnTime   = m_inputManager->getMasterClock() + m_portalOffsetTime;

    delete m_portal;
    m_portal = nullptr;
    m_portalSpawned = false;
}

void Arena::onlineUpdate(){
    // float t_time = m_itemClock->getElapsedTime().asSeconds();
    
    // if(t_time > m_nextSpawnTime){
    //     m_nextSpawnTime = t_time + m_offsetSpawnTime;
    //     if(spawnRandomItem()){
    //         Client::instance().spawnItem(m_lastItemType, m_items.at(m_currentItems)->getX(), m_items.at(m_currentItems)->getY());
    //     }
    // }
}

void Arena::spawnItemAt(int p_type, int x, int y){
    float t_position[3] = {x, y, 0};
    switch (p_type){
        case 0:     { m_items.push_back(new Shield(t_position));     }   break;
        case 1:     { m_items.push_back(new LifeTank(t_position));   }   break;
        case 2:     { m_items.push_back(new Wings(t_position));      }   break;
    }

    m_currentItems = m_items.size();
    m_lastItemType = p_type; 
}

void Arena::setOnline(bool p_state){
    m_online = p_state;
}

bool Arena::getOnline(){
    return m_online;
}

void Arena::pleaseKill(int p_playerIndex){
    //delete m_players[p_playerIndex];
    //m_players[p_playerIndex] = 0;
}

bool Arena::portalIsActive(){
    return m_portalSpawned;
}

float* Arena::getPortalPosition(){
    return m_portal->getPosition();
}

// Gets position of closest item to target position
b2Vec2 Arena::getClosestItemPosition(b2Vec2 p_position){
    m_physicsManager = &PhysicsManager::instance();
    float t_closestDistance = 0.0f;
    b2Vec2 t_return = b2Vec2(0.0f,0.0f);

    for(int i=0; i<m_items.size(); i++){
        if(m_items.at(i)!=nullptr){
            b2Vec2 t_p2 = b2Vec2(m_items.at(i)->getPosition()[0], m_items.at(i)->getPosition()[1]);
            float t_distanceToItem = m_physicsManager->getDistanceBetween(p_position, t_p2);

            // Find closest waypoint
            if(t_closestDistance == 0.0f){ // No waypoint is chosen. Choose this one
                t_closestDistance = t_distanceToItem;
                t_return = t_p2;
            }
            else if(t_distanceToItem < t_closestDistance){
                t_closestDistance = t_distanceToItem;
                t_return = t_p2;
            }
        }
    }
    return t_return;
}