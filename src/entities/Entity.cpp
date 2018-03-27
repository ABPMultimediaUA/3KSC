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

#include "../include/entities/Entity.hpp"
#include "../include/managers/EngineManager.hpp"
#include "../include/managers/PhysicsManager.hpp"
#include <cstring> //For std::memcpy()
#include <iostream>

//Entity count initialization
int Entity::m_entityCount = 0;

EngineManager*  Entity::m_engineManager     = &EngineManager::instance();
PhysicsManager* Entity::m_physicsManager    = &PhysicsManager::instance();

//Create entity with model (proportional scale)
Entity::Entity(float p_position[3], float p_scale, const char* p_modelURL, int p_type){
    m_id = m_entityCount++;    
    float t_scale[3] = {p_scale, p_scale, p_scale};

    for(int i = 0; i < 3; i++){
        m_position[i] = p_position[i];
        m_lastPosition[i] = p_position[i];
    }
    m_engineManager->load3DModel(m_id, p_position, t_scale, p_modelURL);
    moveTo(p_position);

    switch(p_type){
        case 0:
            m_physicsManager->createPhysicBoxPlayer(&m_id, p_position, 5.0, 5.0);
            break;

        case 1: {
            m_engineManager->parseOBJ(p_modelURL);
            m_physicsManager->createPhysicBoxPlatform(&m_id, p_position);
            break;
        }

        case 2:
            m_physicsManager->createPhysicBoxObject(&m_id, p_position, 5.0, 5.0);
            break;

        case 3:
            m_physicsManager->createPhysicBoxPortal(&m_id, p_position, 5.0, 5.0);
            break;

        case 4:
            m_physicsManager->createPhysicBoxPlayer(&m_id, p_position, 5.0, 5.0);
            break;

        case 5:
            m_physicsManager->createPhysicBox(&m_id, p_position, 5.0, 5.0);
            break;

    }
}

Entity::~Entity(){
    m_engineManager->deleteEntity(m_id);
    m_physicsManager->destroyBody(m_id);
}

void Entity::updatePosition(bool p_jumping, bool p_knockback, bool p_dashing){
    if(p_knockback || p_dashing){
        m_position[0] = m_physicsManager->getBody(m_id)->GetPosition().x;
        m_position[1] = m_physicsManager->getBody(m_id)->GetPosition().y;
        m_engineManager->moveEntity(this);
        return;
    }
    if(p_jumping){
        //If we are jumping sleeps the body, so gravity dont affect it
        m_physicsManager->getBody(m_id)->SetAwake(false);
    }
    else{
        //We are falling or in the ground, so we put in the Y coord the value of the body
        m_physicsManager->getBody(m_id)->SetAwake(true);
        m_position[1] = m_physicsManager->getBody(m_id)->GetPosition().y;
    }
    //Add to the body the actual position of the model
    b2Vec2 t_vec(m_position[0], m_position[1]);
    m_physicsManager->getBody(m_id)->SetTransform(t_vec, 0);

    m_engineManager->moveEntity(this);

}

void Entity::moveTo(float p_position[3]){
    std::memcpy(m_position,  p_position, 3 * sizeof(float));
    m_engineManager->moveEntity(this);
}

void Entity::moveX(float p_variation){
    m_lastPosition[0] = m_position[0];
    m_position[0] += p_variation;
    m_engineManager->moveEntity(this);
}

void Entity::moveY(float p_variation){
    m_lastPosition[1] = m_position[1];
    m_position[1] += p_variation;
    m_engineManager->moveEntity(this);
}

void Entity::moveZ(float p_variation){
    m_lastPosition[2] = m_position[2];
    m_position[2] += p_variation;
    m_engineManager->moveEntity(this);
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
    m_engineManager->setRotation(this->getId(), p_degrees);
}

void Entity::setX(float p_position){
    m_lastPosition[0] = m_position[0];
    m_position[0] = p_position;
    m_engineManager->moveEntity(this);
}

void Entity::setY(float p_position){
    m_lastPosition[1] = m_position[1];
    m_position[1] = p_position;
    m_engineManager->moveEntity(this);
}