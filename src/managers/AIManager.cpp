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

#include "../headers/managers/AIManager.hpp"
        
//Instance initialization
AIManager* AIManager::m_instance = 0;

//Returns the only instance of this class
AIManager* AIManager::instance(){
    if (!m_instance)
        m_instance = new AIManager();

    return m_instance;
}

AIManager::AIManager(){}
AIManager::~AIManager(){}

void AIManager::update(){}
void AIManager::buildTree(){}
