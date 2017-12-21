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
#include <iostream>


//Instance initialization
Arena* Arena::m_instance = 0;

Arena::Arena(float p_position[3], float p_scale[3], int p_arenaIndex):Entity(p_position, p_scale){
    EngineManager* t_engineManager = EngineManager::instance();
    if(p_arenaIndex == 1)
        m_modelURL = "assets/models/arenas/stadium.obj";

    t_engineManager->loadArena(m_modelURL);

    m_maxItems      = 4;
    m_currentItems  = 0;
    m_items         = new Item*[m_maxItems];

    m_instance      = this;
}

Arena::~Arena(){}

Arena* Arena::getInstance(){
    return m_instance;
}

void Arena::finishRound(){

}

void Arena::spawnItem(int p_type){
    float positionItem[3] = {30, 5, 0};
    m_items[m_currentItems++] = new Item(p_type, positionItem);
    positionItem[0] = -30;
    m_items[m_currentItems++] = new Item(p_type, positionItem);
    positionItem[0] = 50;
    m_items[m_currentItems++] = new Item(p_type, positionItem);
    positionItem[0] = -50;
    m_items[m_currentItems++] = new Item(p_type, positionItem);
}

//Checks if any of the items in the screen is where the player wants to pick it
//Returns -1 if no item found or the type of the item
int Arena::catchItem(int p_owner, float p_where[3]){
    int t_type = -1;
    
    for (int i = 0; i < m_currentItems; i++){
        //Check not null
        if (m_items[i]){
            //X axis
            if(p_where[0] >= m_items[i]->getX() - 15 && p_where[0] <= m_items[i]->getX() + 15){
                //Y axis
                if(p_where[1] >= m_items[i]->getY() - 15 && p_where[1] <= m_items[i]->getY() + 15){
                    //Use the item
                    m_items[i]->setOwner(p_owner);
                    m_items[i]->use();

                    std::cout << "i: " << i << std::endl;

                    //Save return value and delete item
                    t_type = m_items[i]->getType();
                    delete m_items[i];
                    break;
                }
            }
        }
    }

    return t_type;
}

void Arena::spawnPlayer(){

}

void Arena::movePlatforms(){

}

void Arena::animateBackground(){

}

void Arena::restart(){
    
}