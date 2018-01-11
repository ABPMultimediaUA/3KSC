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
#include "../headers/managers/PhysicsManager.hpp"
#include <cstring> //For std::memcpy()
//#include <iostream>

//Entity count initialization
int Entity::m_entityCount = 0;

//Create a new Entity for a player
Entity::Entity(float p_position[3]){
    m_id = m_entityCount++;
    for(int i = 0; i < 3; i++){
        m_lastPosition[i] = m_position[i];
        m_position[i] = p_position[i];
    }

    EngineManager::instance()->createEntity(m_id, p_position);
    moveTo(p_position);

    float t_dimX = 5.0;
    float t_dimY = 5.0;
    PhysicsManager::instance()->createPhysicBoxPlayer(&m_id, p_position, t_dimX, t_dimY);
}

//Create entity with model (proportional scale)
Entity::Entity(float p_position[3], float p_scale, const char* p_modelURL, int p_type){
    m_id = m_entityCount++;    
    float t_scale[3] = {p_scale, p_scale, p_scale};

    switch (p_type){
        //Players and items
        case 0:{
            for(int i = 0; i < 3; i++){
                m_position[i] = p_position[i];
                m_lastPosition[i] = p_position[i];
            }

            EngineManager::instance()->load3DModel(m_id, p_position, t_scale, p_modelURL);
            moveTo(p_position);

            float t_dimX = 5.0;
            float t_dimY = 6.0;
            PhysicsManager::instance()->createPhysicBoxPlayer(&m_id, p_position, t_dimX, t_dimY);
            break;
        }

        //Arenas
        case 1:{
            EngineManager::instance()->loadArena(p_modelURL);
            PhysicsManager::instance()->createPhysicBoxPlatform(&m_id, p_position, t_scale);
            break;
        }
    }
}

//Create entity with model (free scale)
Entity::Entity(float p_position[3], float p_scale[3], const char* p_modelURL, int p_type){
    m_id = m_entityCount++;

    switch (p_type){
        //Players and items
        case 0:{
            for(int i = 0; i < 3; i++){
                m_position[i] = p_position[i];
                m_lastPosition[i] = p_position[i];
            }

            EngineManager::instance()->load3DModel(m_id, p_position, p_scale, p_modelURL);
            moveTo(p_position);

            float t_dimX = 5.0;
            float t_dimY = 10.0;
            PhysicsManager::instance()->createPhysicBoxPlayer(&m_id, p_position, t_dimX, t_dimY);
            break;
        }

        //Arenas
        case 1:{
            EngineManager::instance()->loadArena(p_modelURL);
            PhysicsManager::instance()->createPhysicBoxPlatform(&m_id, p_position, p_scale);
            break;
        }
    }
}

Entity::~Entity(){
    EngineManager::instance()->deleteEntity(m_id);
    PhysicsManager::instance()->destroyBody(m_id);
}

void Entity::updatePosition(bool p_jumping){
    if(p_jumping){
        PhysicsManager::instance()->getBody(m_id)->PutToSleep();
    }
    else{
        PhysicsManager::instance()->getBody(m_id)->WakeUp();
        m_position[1] = PhysicsManager::instance()->getBody(m_id)->GetPosition().y;
    }
    b2Vec2 t_vec(m_position[0], m_position[1]);
    PhysicsManager::instance()->getBody(m_id)->SetXForm(t_vec, 0);

    EngineManager::instance()->moveEntity(this);
}

void Entity::moveTo(float p_position[3]){
    std::memcpy(m_position,  p_position, 3 * sizeof(float));
    EngineManager::instance()->moveEntity(this);
}

void Entity::moveX(float p_variation){
    m_lastPosition[0] = m_position[0];
    m_position[0] += p_variation;
    EngineManager::instance()->moveEntity(this);
}

void Entity::moveY(float p_variation){
    m_lastPosition[1] = m_position[1];
    m_position[1] += p_variation;
    EngineManager::instance()->moveEntity(this);
}

void Entity::moveZ(float p_variation){
    m_lastPosition[2] = m_position[2];
    m_position[2] += p_variation;
    EngineManager::instance()->moveEntity(this);
}

//Checks if an entity is close to a certain point (in specified range)
bool Entity::checkCloseness(float* p_point, float p_range){  
    //X axis
    if(p_point[0] >= m_position[0] - p_range && p_point[0] <= m_position[0] + p_range){
        //Y axis
        if(p_point[1] >= m_position[1] - p_range && p_point[1] <= m_position[1] + p_range){
            return true;
        }
    }   
    return false;
}

int Entity::getId(){
    return m_id;
}

float* Entity::getPosition(){
    return m_position;
}

float Entity::getX(){
    return m_position[0];
}

float Entity::getY(){
    return m_position[1];
}

float Entity::getZ(){
    return m_position[2];
}

int Entity::getEntityCount(){
    return Entity::m_entityCount;
}

void Entity::rotate(float p_degrees){
    EngineManager::instance()->setRotation(this->getId(), p_degrees);
}