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

//Entity count initialization
int Entity::m_entityCount = 0;

//Create a new Etity for a player
Entity::Entity(float p_position[3]){
    m_id = m_entityCount++;

    for(int i = 0; i < 3; i++){
        m_position[i] = p_position[i];
        m_lastPosition[i] = p_position[i];
    }

    EngineManager::instance()->createEntity(m_id, p_position);
    moveTo(p_position);

    //Create a new body and positioning it in the coords of the Entity
    m_bodyDef = new b2BodyDef();
    m_bodyDef->position.Set(p_position[0], p_position[1]);
    m_body = PhysicsManager::instance()->getWorld()->CreateBody(m_bodyDef);

    //Create a shape for the body
    m_shapeDef = new b2PolygonDef();
    m_shapeDef->SetAsBox(5.0, 5.0);
    m_shapeDef->density = 10.0;
    m_shapeDef->friction = 0.3;

    //Attach the shape to the body
    m_body->CreateShape(m_shapeDef);
    m_body->SetMassFromShapes();

    m_polygonShape = new b2PolygonShape(m_shapeDef);
}

b2PolygonShape* Entity::getShape(){
    return m_polygonShape;
}

b2Body* Entity::getBody(){
    return m_body;
}

//Create a new Entity for a new Platform or Arena
Entity::Entity(float p_position[3], float p_scale[3]){
    /*
    m_id = m_entityCount++;

    EngineManager* t_engineManager = EngineManager::instance();
    t_engineManager->createEntity(m_id, p_position);
    t_engineManager->scale(m_id, p_scale);
    moveTo(p_position);
    */

    m_bodyDef = new b2BodyDef();
    m_bodyDef->position.Set(p_position[0], p_position[1]);
    
    m_body = PhysicsManager::instance()->getWorld()->CreateBody(m_bodyDef);

    m_shapeDef = new b2PolygonDef();

    //scaleX = 50
    m_shapeDef->SetAsBox((p_scale[0] * 10), p_scale[1]);
    m_body->CreateShape(m_shapeDef);

    m_polygonShape = new b2PolygonShape(m_shapeDef);
}

Entity::~Entity(){}

void Entity::updatePosition(float p_posY, bool p_jumping){
    //std::cout << m_position[0] << "," << m_position[1] << std::endl;
    if(p_jumping){
        this->m_body->PutToSleep();
    }
    else{
        m_body->WakeUp();
        m_position[1] = p_posY;
    }
    b2Vec2 t_vec(m_position[0], m_position[1]);
    m_body->SetXForm(t_vec, 0);

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
