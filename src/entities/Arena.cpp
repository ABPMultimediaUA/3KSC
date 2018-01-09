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

#include "../headers/entities/Arena.hpp"
#include "../headers/managers/EngineManager.hpp"
//#include <iostream>


//Instance initialization
Arena* Arena::m_instance = 0;

Arena::Arena(float p_position[3], float p_scale[3], int p_arenaIndex):Entity(p_position, p_scale){
    EngineManager* t_engineManager = EngineManager::instance();
    if(p_arenaIndex == 1)
        m_modelURL = "assets/models/arenas/stadium.obj";

    t_engineManager->loadArena(m_modelURL);

    m_maxItems      = 8;
    m_currentItems  = 0;
    m_items         = new Item*[m_maxItems];

    m_instance      = this;
}

Arena::~Arena(){}

Arena* Arena::getInstance(){
    return m_instance;
}

void Arena::spawnPlayers(){
    float positionRawr[3] = {-10, 20, 0};
    float positionPlup[3] = {10, 20, 0};

    m_playerCount = 0;
    m_players = new Character*[4];

    m_players[m_playerCount++] = new Rawr("Player 1", positionRawr, -1);
    //m_players[m_playerCount++] = new Plup("Player 2", positionPlup, -2);
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
    float positionItem[3] = {-100, 10, 0};
    /*
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
    m_items[m_currentItems++] = new Item(2, positionItem);
    */
}

//Checks if any of the items in the screen is where the player wants to pick it
//Returns -1 if no item found or the type of the item
int Arena::catchItem(int p_owner, float p_where[3]){
    int t_type = -1;
    
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

                    //Save return value and delete item
                    t_type = m_items[i]->getType();
                    delete m_items[i];
                    m_items[i] = 0;
                    break;
                }
            }
        }
    }

    return t_type;
}

void Arena::finishRound(){

}

void Arena::movePlatforms(){

}

void Arena::animateBackground(){

}

void Arena::restart(){
    
}