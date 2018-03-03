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

#include "../include/AI/AIMiyagi.hpp"
#include "../include/AI/AINode.hpp"
#include "../include/entities/characters/Character.hpp"
#include "../include/managers/PhysicsManager.hpp"
#include "../include/entities/Arena.hpp"
#include <iostream>
#include <string>
        
//Returns the only instance of this class
AIMiyagi& AIMiyagi::instance(){
    static AIMiyagi instance;
    return instance;
}

AIMiyagi::AIMiyagi(){
    m_physicsManager    = &PhysicsManager::instance();
    m_arena             = Arena::getInstance();
}

// Updates all the variables required by the tree to work properly
void AIMiyagi::update(){
    
}

// Builds the tree containing Kira's AI. Builds all the trues to a node. If no trues are left, builds the falses and repeats itself with the next node
void AIMiyagi::buildTree(){
    
}
