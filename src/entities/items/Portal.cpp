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

#include "../../include/entities/items/Portal.hpp"
#include "../../include/managers/PhysicsManager.hpp"
#include "../../include/entities/Arena.hpp"
#include <iostream>

//Constructor
Portal::Portal(float p_position[3])
    : Entity(p_position, 4.f, "assets/models/items/portal.obj", 3){
    m_arena             = Arena::getInstance();
    m_physicsManager    = &PhysicsManager::instance();
    m_using             = false;
    m_charge            = 0.0f;
    m_charactersInPortal = 0;
    m_physicsManager->addDataToPortal(this);
}

//Destructor
Portal::~Portal(){
    std::cout << "1.5" << std::endl;
    //delete m_physicsManager;
   // delete m_arena;
    std::cout << "2" << std::endl;
}

void Portal::onEnter(Character* p_character){
    m_charactersInPortal++;
    m_players[p_character->getIndex()] = p_character;
    m_using = true;
}


void Portal::onLeave(Character* p_character){
    m_players[p_character->getIndex()] = NULL;
    m_charactersInPortal--;
    m_using = false;
}

void Portal::update(float p_delta){
    if(m_using && m_charactersInPortal == 1){
        m_charge += p_delta;
        if(m_charge >= 4){
    
            use();
            m_charge = 0;
        }
    }
}
//Increases owner's ultimate bar
void Portal::use(){
    uint i;
    for(i = 0; i < 4; i++)
    {
        if(m_players[i]!= NULL)
        {
            m_players[i]->setUltimateCharged();
            break;
        }
    }
    std::cout << m_players[i]->getIndex() <<" filled ultimate bar." << std::endl;

    m_arena->hidePortal();
    m_using             = false;
    m_charge            = 0.0f;
    m_charactersInPortal = 1;
    
}