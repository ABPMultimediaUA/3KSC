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

#include "../headers/entities/Item.hpp"
#include "../headers/managers/PhysicsManager.hpp"
#include "../headers/entities/Arena.hpp"
//#include <iostream>

//Static members
const char* Item::m_modelURLs[4] = {"assets/models/items/life_tank.obj", "assets/models/items/shield.obj", "assets/models/items/movement_wings.obj", "assets/models/items/life_tank.obj"};

Item::Item(int p_type, float p_position[3]):Entity(p_position, 4.f, Item::m_modelURLs[p_type]){
    m_type = p_type;
}

Item::~Item(){}

int Item::getType(){
    return m_type;
}

void Item::setOwner(int p_owner){
    m_owner = p_owner;
}

void Item::use(){
    switch (m_type){
        //Life tank
        case 0:{
            Arena::getInstance()->getPlayer(m_owner)->changeLife(30);
            break;
        }

        //Shield
        case 1:{
            Arena::getInstance()->getPlayer(m_owner)->shield();
            break;
        }

        //Wings
        case 2:{
            Arena::getInstance()->getPlayer(m_owner)->wings();
            break;
        }

        //Fosforian Obedience Automatic Hammer (F.O.A.H)
        case 3:{

            break;
        }
    }
}

