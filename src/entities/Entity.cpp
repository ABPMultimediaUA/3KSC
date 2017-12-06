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
#include "../headers/managers/EngineManager.hpp"
#include <cstring> //For std::memcpy()

//Entity count initialization
int Entity::m_entityCount = 0;

Entity::Entity(float p_position[3]){
    m_id = m_entityCount++;

    EngineManager::instance()->createEntity(m_id, p_position);
    moveTo(p_position);
}

Entity::Entity(float p_position[3], float p_scale[3]){
    m_id = m_entityCount++;

    EngineManager* t_engineManager = EngineManager::instance();
    t_engineManager->createEntity(m_id, p_position);
    t_engineManager->scale(m_id, p_scale);
    moveTo(p_position);
}

Entity::~Entity(){}

void Entity::moveTo(float p_position[3]){
    std::memcpy(m_position,  p_position, 3 * sizeof(float));
    EngineManager::instance()->moveEntity(this);
}

void Entity::moveX(float p_variation){
    m_position[0] += p_variation;
    EngineManager::instance()->moveEntity(this);
}

void Entity::moveY(float p_variation){
    m_position[1] += p_variation;
    EngineManager::instance()->moveEntity(this);
}

void Entity::moveZ(float p_variation){
    m_position[2] += p_variation;
    EngineManager::instance()->moveEntity(this);
}


int Entity::getId(){
    return m_id;
}

float* Entity::getPosition(){
    return m_position;
}