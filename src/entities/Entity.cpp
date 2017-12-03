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

#include "../headers/entities/Entity.hpp"
#include "../headers/managers/GraphicManager.hpp"
#include <cstring> //For std::memcpy()

//Entity count initialization
int Entity::m_entityCount = 0;

Entity::Entity(float p_position[3]){
    m_id = m_entityCount++;

    GraphicManager* t_graphicManager = GraphicManager::instance();
    t_graphicManager->createCube(m_id, p_position);
    moveTo(p_position);
}

Entity::Entity(float p_position[3], float p_scale[3]){
    m_id = m_entityCount++;

    GraphicManager* t_graphicManager = GraphicManager::instance();
    t_graphicManager->createCube(m_id, p_position);
    t_graphicManager->scaleNode(m_id, p_scale);
    moveTo(p_position);
}

Entity::~Entity(){}

void Entity::moveTo(float p_position[3]){
    std::memcpy(m_position,  p_position, 3 * sizeof(float));
}

void Entity::moveX(float p_variation){
    m_position[0] += p_variation;
}

void Entity::moveY(float p_variation){
    m_position[1] += p_variation;
}

void Entity::moveZ(float p_variation){
    m_position[2] += p_variation;
}


int Entity::getId(){
    return m_id;
}