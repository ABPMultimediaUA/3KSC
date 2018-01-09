/*
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
    along with this program.  If not, see http://www.gnu.org/licenses/.

    You can contact Chaotic Games at: chaoticgamesdev@gmail.com
*/

#include "../headers/managers/PhysicsManager.hpp"
#include "../headers/debug.hpp"


//Instance initialization
PhysicsManager* PhysicsManager::m_instance = 0;

//Returns the only instance of this class
PhysicsManager* PhysicsManager::instance(){
    if (!m_instance)
        m_instance = new PhysicsManager();

    return m_instance;
}
  //at global scope

//Constructor
PhysicsManager::PhysicsManager(){
    m_worldAABB = b2AABB();
    b2Vec2 t_upperBound(200.f, 200.f);
    b2Vec2 t_lowerBound(-200.f, -200.f);
    m_worldAABB.upperBound = t_upperBound;
    m_worldAABB.lowerBound = t_lowerBound;

    m_gravity = b2Vec2(0.0f, -10.0f);
    
    m_doSleep = true;

    m_world = new b2World(m_worldAABB, m_gravity, m_doSleep);

    m_timeStep = 3.0 / 60.0;
    m_iterations = 10;
}
//Destructor
PhysicsManager::~PhysicsManager(){}

void PhysicsManager::createPhysicBoxPlayer(int* p_id, float p_position[3], float p_dimX, float p_dimY){
    //Create a new body and positioning it in the coords of the Entity
    m_bodyDef = new b2BodyDef();
    m_bodyDef->position.Set(p_position[0], p_position[1]);
    m_body = m_world->CreateBody(m_bodyDef);

    //Create a shape for the body
    m_shapeDef = new b2PolygonDef();
    m_shapeDef->SetAsBox(p_dimX, p_dimY);
    m_shapeDef->density = 10.0;
    m_shapeDef->friction = 0.3;

    //Attach the shape to the body
    m_body->CreateShape(m_shapeDef);
    m_body->SetMassFromShapes();
    m_body->SetUserData(p_id);

    //NO ENTIENDO PORQUE PERO SI QUITAS ESTO PETA
    int *t_id = static_cast<int*>(m_body->GetUserData());

    m_polygonShape = new b2PolygonShape(m_shapeDef);
}

void PhysicsManager::createPhysicBoxPlatform(int* p_id, float p_position[3], float p_scale[3]){
    m_bodyDef = new b2BodyDef();
    m_bodyDef->position.Set(p_position[0], p_position[1]);
    
    m_body = m_world->CreateBody(m_bodyDef);

    m_shapeDef = new b2PolygonDef();

    //scaleX = 50
    m_shapeDef->SetAsBox((p_scale[0] * 10), p_scale[1]);
    m_body->CreateShape(m_shapeDef);
    m_body->SetUserData(p_id);    

    m_polygonShape = new b2PolygonShape(m_shapeDef);
}

b2World* PhysicsManager::getWorld(){
    return m_world;
}

b2PolygonShape* PhysicsManager::getShape(){
    return m_polygonShape;
}

//An ID is receive and we look for the body with that ID
b2Body* PhysicsManager::getBody(int p_id){
    b2Body* t_body = m_world->GetBodyList();
    int* t_id = 0;
    int  t_value = 0;

    while(t_body != NULL){
        t_id = static_cast<int*>(t_body->GetUserData());
        t_value = *t_id;
        if(p_id == t_value)
            return t_body;
        
        t_body = t_body->GetNext();
    }

    return 0;
}

float PhysicsManager::getTimeStep(){
    return m_timeStep;
}

int PhysicsManager::getIterations(){
    return m_iterations;
}


//Adds a force to an entity
void PhysicsManager::addForce(){

}

//Removes a force from an entity
void PhysicsManager::removeForce(){

}

//Handles gravity changes in Kawaiisaki map
void PhysicsManager::updateGravity(){

}