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
    m_arena     = Arena::getInstance();
    m_using     = false;
    m_charge    = 1.0f;
}

//Destructor
Portal::~Portal(){
    // delete m_physicsManager;
    delete m_arena;
}

void Portal::onEnter(){
    std::cout<<"entro portal"<<std::endl;
    m_using = true;
}

void Portal::onLeave(){
    std::cout<<"salgo portal"<<std::endl;
    m_using = false;
}

void Portal::update(float p_delta){
    if(m_using){
        m_charge += p_delta;
        //std::cout<<p_delta<<std::endl;
    }
    
    std::cout<<m_charge<<std::endl;
    if(m_charge > 10){
        //m_arena->get
        m_charge = 0;
    }
}
//Increases owner's ultimate bar
/* void Portal::use(){
    std::cout << m_arena->getPlayer(m_owner)->getName() <<" filled ultimate bar." << std::endl
    << std::endl;
}

//Sets the owner of the item
void Portal::setOwner(int p_owner){
    m_owner = p_owner;
} */