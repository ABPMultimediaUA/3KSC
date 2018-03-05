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

#include "../include/managers/PhysicsManager.hpp"
#include "../include/managers/EngineManager.hpp"
#include "../include/entities/Arena.hpp"
#include "../include/debug.hpp"
#include <iostream>

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
    //b2Vec2 gravity(0.0f, 0.0f);
    b2Vec2 gravity(0.0f, -10.0f);

    m_world = new b2World(gravity);

    m_timeStep = 10.f/60.0f;
    m_velocityIterations = 6;
    m_positionIterations = 2;

    m_contactManager = new ContactManager();

    m_world->SetContactListener(m_contactManager);
}
//Destructor
PhysicsManager::~PhysicsManager(){}

void PhysicsManager::createPhysicBoxPlayer(int* p_id, float p_position[3], float p_dimX, float p_dimY){
    //Create a new body and positioning it in the coords of the Entity
    m_bodyDef = new b2BodyDef();
    m_bodyDef->type = b2_dynamicBody;
    m_bodyDef->position.Set(p_position[0], p_position[1]);
    m_body = m_world->CreateBody(m_bodyDef);

    //Create a shape for the body
    m_polygonShape = new b2PolygonShape();
    m_polygonShape->SetAsBox(p_dimX, p_dimY);
    
    m_fixtureDef = new b2FixtureDef();
    m_fixtureDef->shape = m_polygonShape;
    m_fixtureDef->density = 1.0f;
    m_fixtureDef->friction = 0.3f;

    //Attach the shape to the body
    m_body->CreateFixture(m_fixtureDef);
    m_body->SetUserData(p_id);

    //NO ENTIENDO PORQUE PERO SI QUITAS ESTO PETA
    int *t_id = static_cast<int*>(m_body->GetUserData());

    //add foot sensor fixture
    m_polygonShape->SetAsBox(0.3, 0.3, b2Vec2(-2,-5), 0);
    m_fixtureDef->isSensor = true;
    b2Fixture* footSensorFixture = m_body->CreateFixture(m_fixtureDef);
    footSensorFixture->SetUserData( (void*)999 );
}

void PhysicsManager::createPhysicBoxObject(int* p_id, float p_position[3], float p_dimX, float p_dimY){
    //Create a new body and positioning it in the coords of the Entity
    m_bodyDef = new b2BodyDef();
    m_bodyDef->type = b2_dynamicBody;
    m_bodyDef->position.Set(p_position[0], p_position[1]);
    m_body = m_world->CreateBody(m_bodyDef);

    //Create a shape for the body
    m_polygonShape = new b2PolygonShape();
    m_polygonShape->SetAsBox(p_dimX, p_dimY);
    
    m_fixtureDef = new b2FixtureDef();
    m_fixtureDef->shape = m_polygonShape;
    m_fixtureDef->density = 1.0f;
    m_fixtureDef->friction = 0.3f;

    //Attach the shape to the body
    m_body->CreateFixture(m_fixtureDef);
    m_body->SetUserData(p_id);

    //NO ENTIENDO PORQUE PERO SI QUITAS ESTO PETA
    int *t_id = static_cast<int*>(m_body->GetUserData());
}

void PhysicsManager::createPhysicBoxPlatform(int* p_id, float p_position[3], float p_scale[3], int p_arenaIndex){
    m_bodyDef = new b2BodyDef();
    m_bodyDef->position.Set(0.0f, 0.0f);
    
    m_body = m_world->CreateBody(m_bodyDef);
    //m_body->SetUserData(p_id);

    m_polygonShape = new b2PolygonShape();
    //if(p_arenaIndex == 0){ 
    float t_minX, t_maxX;
    float t_minY, t_maxY;
    float t_dimX, t_dimY;
    float t_factor = 4.5;

    for(int i = 0; i < EngineManager::instance()->getTotalVertex()-2; i++){
        t_minX = EngineManager::instance()->getTotalVertexX().at(i*2);
        t_maxX = EngineManager::instance()->getTotalVertexX().at((i*2)+1);

        t_minY = EngineManager::instance()->getTotalVertexY().at(i*2);
        t_maxY = EngineManager::instance()->getTotalVertexY().at((i*2)+1);

        if(t_minX >= 0 && t_maxX > 0)
            t_dimX = (t_maxX - t_minX) * t_factor;
        else if(t_minX < 0 && t_maxX <= 0)
            t_dimX = (abs(t_minX) - abs(t_maxX)) * t_factor;
        else
            t_dimX = (abs(t_minX) + t_maxX) * t_factor;

        if(t_minY >= 0 && t_maxY > 0)
            t_dimY = (t_maxY - t_minY) * t_factor;
        else if(t_minY < 0 && t_maxY <= 0)
            t_dimY = (abs(t_minY) - abs(t_maxY)) * t_factor;
        else
            t_dimY = (abs(t_minY) + t_maxY) * t_factor;

        //std::cout << t_dimX << std::endl;
        //std::cout << t_dimY << std::endl;

        if(t_minX < 0 && t_maxX > 0)
            m_polygonShape->SetAsBox(t_dimX, t_dimY, b2Vec2((t_minX + t_maxX) ,(t_minY*11)), 0);
        else if(t_minX >= 0)
            m_polygonShape->SetAsBox(t_dimX, t_dimY, b2Vec2((t_minX*26.3) ,(t_minY*11)), 0);
        else
            m_polygonShape->SetAsBox(t_dimX, t_dimY, b2Vec2((t_maxX*26.3) ,(t_minY*11)), 0);
        
        m_body->CreateFixture(m_polygonShape, 0.0f);
    }

    /*
    }else if(p_arenaIndex == 1){
        //Nenufar izquierda
        m_polygonShape->SetAsBox(20, 1, b2Vec2(-25,0), 0);
        m_body->CreateFixture(m_polygonShape, 0.0f);
        
        //Nenufar derecha
        m_polygonShape->SetAsBox(20, 1, b2Vec2(200,0), 0);
        m_body->CreateFixture(m_polygonShape, 0.0f);

        //Plataforma central
        m_polygonShape->SetAsBox(80, 1, b2Vec2(90,0), 0);
        m_body->CreateFixture(m_polygonShape, 0.0f);
        
        //Arbol izquierda rama grande
        m_polygonShape->SetAsBox(32, 1, b2Vec2(-9,40), 0);
        m_body->CreateFixture(m_polygonShape, 0.0f);
        
        //Arbol izquierda rama pequeña
        m_polygonShape->SetAsBox(16, 1, b2Vec2(-9,60), 0);
        m_body->CreateFixture(m_polygonShape, 0.0f);

        //Arbol derecha rama grande
        m_polygonShape->SetAsBox(32, 1, b2Vec2(182,40), 0);
        m_body->CreateFixture(m_polygonShape, 0.0f);
        
        //Arbol derecha rama pequeña
        m_polygonShape->SetAsBox(8, 1, b2Vec2(172,65), 0);
        m_body->CreateFixture(m_polygonShape, 0.0f);
    }
    */
}

b2World* PhysicsManager::getWorld(){
    return m_world;
}

b2PolygonShape* PhysicsManager::getShape(int p_id){
    b2Body* t_body = m_world->GetBodyList();
    b2Shape* t_shape = 0;
    int* t_id = 0;
    int  t_value = 0;

    while(t_body != NULL){
        t_id = static_cast<int*>(t_body->GetUserData());
        t_value = *t_id;
        if(p_id == t_value){
            t_shape = t_body->GetFixtureList()->GetShape();
            if(t_shape->GetType() == 1){
                b2PolygonShape* t_polygonShape = (b2PolygonShape*)t_shape;
                return t_polygonShape;
            }
        }        
        t_body = t_body->GetNext();
    }
    return 0;
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

//Destroys the body with the given ID
void PhysicsManager::destroyBody(int p_id){
    b2Body* t_body = getBody(p_id);
    m_world->DestroyBody(t_body);
}

int32 PhysicsManager::getVelocityIterations(){
    return m_velocityIterations;
}

int32 PhysicsManager::getPositionIterations(){
    return m_positionIterations;
}

float32 PhysicsManager::getTimeStep(){
    return m_timeStep;
}

//Adds a force to an entity
void PhysicsManager::addForce(){}

//Removes a force from an entity
void PhysicsManager::removeForce(){}

//Handles gravity changes in Kawaiisaki map
void PhysicsManager::updateGravity(){}

//Casts a ray between 2 points and returns the a number between 0 and 1. 1 is max distance collision.
float PhysicsManager::RaycastBetween(b2Vec2 p_p1, b2Vec2 p_p2){
    //set up input
    b2RayCastInput t_input;
    t_input.p1 = p_p1;
    t_input.p2 = p_p2;
    t_input.maxFraction = 1;
  
    //check every fixture of every body to find closest
    float t_closestFraction = 1; //start with end of line as p2

    for (b2Body* b = m_world->GetBodyList(); b; b = b->GetNext()) {
        for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext()) {
  
            b2RayCastOutput t_output;
            if ( ! f->RayCast( &t_output, t_input, 0 ) ) // No collision
                continue;
            if ( t_output.fraction < t_closestFraction ) {
                t_closestFraction = t_output.fraction;
            }            
        }
    }
    return t_closestFraction;
}

//Returns the position to the closest character to p_p1
Character* PhysicsManager::getClosestCharacter(b2Vec2 p_p1){
    int t_playerCount = Arena::getInstance()->getPlayerCount();
    Character* t_currentPlayer;
    Character* t_closestPlayer;
    float t_shortestModule = 0;

    for (int i = 0; i < t_playerCount; i++){
        t_currentPlayer = Arena::getInstance()->getPlayer(i);
        float t_target_x = t_currentPlayer->getX();
        float t_target_y = t_currentPlayer->getY();
        float t_target_z = t_currentPlayer->getZ();

        b2Vec2 t_p2 = b2Vec2(t_target_x, t_target_y); 

        b2Vec2 t_p2p1 = b2Vec2(t_target_x - p_p1.x, t_target_y - p_p1.y);

        float t_module = sqrt(pow(t_p2p1.x,2) + pow(t_p2p1.y,2));

        //We consider this as if the character is itself
        if(t_module <= 0.5)
            continue;

        if(t_shortestModule==0){
            t_shortestModule = t_module;
        }
        else{
            if(t_module < t_shortestModule){
                t_shortestModule = t_module;
                t_closestPlayer = t_currentPlayer;
            }
        }
    }

    return(t_closestPlayer);
}

float PhysicsManager::getDistanceToClosestCharacter(b2Vec2 p_p1){
    Character* t_closestPlayer = getClosestCharacter(p_p1);
    float t_target_x = t_closestPlayer->getX();
    float t_target_y = t_closestPlayer->getY();
    float t_target_z = t_closestPlayer->getZ();

    b2Vec2 t_p2 = b2Vec2(t_target_x, t_target_y); 

    b2Vec2 t_p2p1 = b2Vec2(t_target_x - p_p1.x, t_target_y - p_p1.y);

    float t_module = sqrt(pow(t_p2p1.x,2) + pow(t_p2p1.y,2));

    return(t_module);
}

bool PhysicsManager::isTouchingGround(){
    if(getContactManager()->getJump() > 1)
        return true;
    else
        return false;
}

ContactManager* PhysicsManager::getContactManager(){
    return m_contactManager;
}