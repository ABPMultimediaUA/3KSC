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

#include "../include/AI/AILuka.hpp"
#include "../include/managers/PhysicsManager.hpp"
#include "../include/entities/characters/Character.hpp"
#include "../include/entities/Arena.hpp"
#include <iostream>
#include <string>
        
//Returns the only instance of this class
AILuka& AILuka::instance(){
    static AILuka instance;
    return instance;
}

AILuka::AILuka(){
    m_physicsManager    = &PhysicsManager::instance();
    m_arena             = Arena::getInstance();
}

AILuka::~AILuka(){
    
}

// Updates all the variables required by the tree to work properly
void AILuka::update(){
    
}

// Builds the tree containing Luka's AI. Builds all the trues to a node. If no trues are left, builds the falses and repeats itself with the next node
void AILuka::buildTree(){
    
}
