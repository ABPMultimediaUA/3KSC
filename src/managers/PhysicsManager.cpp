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

EngineManager* PhysicsManager::m_engineManager = 0;

//Returns the only instance of this class
PhysicsManager& PhysicsManager::instance(){
    static PhysicsManager instance;
    return instance;
}
  //at global scope

//Constructor
PhysicsManager::PhysicsManager(){
    m_engineManager = &EngineManager::instance();

    b2Vec2 gravity(0.0f, -10.0f);

    m_world = new b2World(gravity);

    m_timeStep = 10.f/60.0f;
    m_velocityIterations = 6;
    m_positionIterations = 2;

    m_contactManager = new ContactManager();
    m_world->SetContactListener(m_contactManager);

    CATEGORY_PLAYER = 0x0001;
    CATEGORY_ITEM   = 0x0002;
    CATEGORY_GROUND = 0x0003;
}
//Destructor
PhysicsManager::~PhysicsManager(){}

void PhysicsManager::update(){
    m_world->Step(m_timeStep, m_velocityIterations, m_positionIterations);
}

void PhysicsManager::createPhysicBoxPlayer(int* p_id, float p_position[3], float p_dimX, float p_dimY){
    //Create a new body and positioning it in the coords of the Entity
    b2BodyDef* t_bodyDef = new b2BodyDef();
    t_bodyDef->type = b2_dynamicBody;
    t_bodyDef->position.Set(p_position[0], p_position[1]);
    b2Body* t_body = m_world->CreateBody(t_bodyDef);

    //Create a shape for the body
    b2PolygonShape* t_polygonShape = new b2PolygonShape();
    t_polygonShape->SetAsBox(p_dimX, p_dimY);
    
    b2FixtureDef* t_fixtureDef = new b2FixtureDef();
    t_fixtureDef->shape = t_polygonShape;
    t_fixtureDef->density = 1.0f;
    t_fixtureDef->friction = 0.3f;
    t_fixtureDef->filter.categoryBits = CATEGORY_PLAYER;
    t_fixtureDef->filter.maskBits     = CATEGORY_ITEM | CATEGORY_GROUND;
    t_fixtureDef->filter.groupIndex   = -1;

    //Attach the shape to the body
    t_body->CreateFixture(t_fixtureDef);
    t_body->SetUserData(p_id);

    m_playersBody.push_back(t_body);
}

void PhysicsManager::setPlayerSensor(int p_id, Character* p_character){
    b2Body* t_body = getBody(p_id);
    float t_tam = 10;
    b2PolygonShape* t_polygonShape = new b2PolygonShape();
    t_polygonShape->SetAsBox(0.3, 0.3, b2Vec2(-2,-5), 0);
    //t_polygonShape->SetAsBox(t_tam, t_tam/4);
    
    b2FixtureDef* t_fixtureDef = new b2FixtureDef();
    t_fixtureDef->shape = t_polygonShape;
    t_fixtureDef->isSensor = true;

    //Attach the shape to the body
    t_body->CreateFixture(t_fixtureDef);

    b2Fixture* footSensorFixture = t_body->CreateFixture(t_fixtureDef);
    footSensorFixture->SetUserData(p_character);
}

void PhysicsManager::createPhysicBoxObject(int* p_id, float p_position[3], float p_dimX, float p_dimY){
    //Create a new body and positioning it in the coords of the Entity
    b2BodyDef* t_bodyDef = new b2BodyDef();
    t_bodyDef->type = b2_dynamicBody;
    t_bodyDef->position.Set(p_position[0], p_position[1]);
    b2Body* t_body = m_world->CreateBody(t_bodyDef);

    //Create a shape for the body
    b2PolygonShape* t_polygonShape = new b2PolygonShape();
    t_polygonShape->SetAsBox(p_dimX, p_dimY);
    
    b2FixtureDef* t_fixtureDef = new b2FixtureDef();
    t_fixtureDef->shape = t_polygonShape;
    t_fixtureDef->density = 1.0f;
    t_fixtureDef->friction = 0.3f;
    t_fixtureDef->filter.categoryBits = CATEGORY_ITEM;
    t_fixtureDef->filter.maskBits     = CATEGORY_PLAYER | CATEGORY_GROUND;
    t_fixtureDef->filter.groupIndex   = -1;

    //Attach the shape to the body
    t_body->CreateFixture(t_fixtureDef);
    t_body->SetUserData(p_id);
}

void PhysicsManager::createPhysicBoxPlatform(int* p_id, float p_position[3]){
    b2BodyDef* t_bodyDef = new b2BodyDef();
    t_bodyDef->position.Set(0.0f, 0.0f);
    
    b2Body* t_body = m_world->CreateBody(t_bodyDef);

    b2PolygonShape* t_polygonShape = new b2PolygonShape();
    float t_minX, t_maxX;
    float t_minY, t_maxY;
    float t_dimX, t_dimY;
    float t_factor = 4.5;

    for(int i = 0; i < m_engineManager->getTotalVertex()-2; i++){
        t_minX = m_engineManager->getTotalVertexX().at(i*2);
        t_maxX = m_engineManager->getTotalVertexX().at((i*2)+1);

        t_minY = m_engineManager->getTotalVertexY().at(i*2);
        t_maxY = m_engineManager->getTotalVertexY().at((i*2)+1);

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

        if(t_minX < 0 && t_maxX > 0)
            t_polygonShape->SetAsBox(t_dimX, t_dimY, b2Vec2((t_minX + t_maxX) ,(t_minY*11)), 0);
        else if(t_minX >= 0)
            t_polygonShape->SetAsBox(t_dimX, t_dimY, b2Vec2((t_minX*26.3) ,(t_minY*11)), 0);
        else
            t_polygonShape->SetAsBox(t_dimX, t_dimY, b2Vec2((t_maxX*26.3) ,(t_minY*11)), 0);
        
        b2FixtureDef* t_fixtureDef = new b2FixtureDef();
        t_fixtureDef->shape = t_polygonShape;
        t_fixtureDef->filter.categoryBits = CATEGORY_GROUND;
        t_fixtureDef->filter.maskBits     = CATEGORY_PLAYER | CATEGORY_ITEM;

        t_body->CreateFixture(t_fixtureDef);
    }
}

void PhysicsManager::createPhysicBoxPortal(int* p_id, float p_position[3], float p_dimX, float p_dimY){
    float size = 10;
    b2BodyDef* t_bodyDef = new b2BodyDef();
    t_bodyDef->type = b2_dynamicBody;
    t_bodyDef->position.Set(p_position[0]-size/2 , p_position[1]);
    b2Body* t_body = m_world->CreateBody(t_bodyDef);
    
    //Create a shape for the body
    b2PolygonShape* t_polygonShape = new b2PolygonShape();
    t_polygonShape->SetAsBox(size,size/4);
    
    b2FixtureDef* t_fixtureDef = new b2FixtureDef();
    t_fixtureDef->shape = t_polygonShape;
    t_fixtureDef->density = 1.0f;
    t_fixtureDef->friction = 0.3f;
    t_fixtureDef->filter.categoryBits = CATEGORY_ITEM;
    t_fixtureDef->filter.maskBits     = CATEGORY_PLAYER | CATEGORY_GROUND;
    t_fixtureDef->filter.groupIndex   = -1;

    //Attach the shape to the body
    b2Fixture* portalSensor = t_body->CreateFixture(t_fixtureDef);
    portalSensor ->SetUserData((void*)888);
}

void PhysicsManager::createPhysicBox(int* p_id, float p_position[3], float p_dimX, float p_dimY){
    //Create a new body and positioning it in the coords of the Entity
    b2BodyDef* t_bodyDef = new b2BodyDef();
    t_bodyDef->type = b2_dynamicBody;
    t_bodyDef->position.Set(p_position[0], p_position[1]);
    b2Body* t_body = m_world->CreateBody(t_bodyDef);

    //Create a shape for the body
    b2PolygonShape* t_polygonShape = new b2PolygonShape();
    t_polygonShape->SetAsBox(p_dimX, p_dimY);
    
    b2FixtureDef* t_fixtureDef = new b2FixtureDef();
    t_fixtureDef->shape = t_polygonShape;

    //Attach the shape to the body
    t_body->CreateFixture(t_fixtureDef);
    t_body->SetUserData(p_id);
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
            if ( !f->RayCast( &t_output, t_input, 0 ) ) // No collision
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
    t_closestPlayer = 0;
    float t_shortestModule = 0;

    for (int i = 0; i < t_playerCount; i++){
        t_currentPlayer = Arena::getInstance()->getPlayer(i);
        float t_target_x = t_currentPlayer->getX();
        float t_target_y = t_currentPlayer->getY();
        float t_target_z = t_currentPlayer->getZ();

        b2Vec2 t_p2p1 = b2Vec2(t_target_x - p_p1.x, t_target_y - p_p1.y);

        float t_module = abs(sqrt(pow(t_p2p1.x,2) + pow(t_p2p1.y,2)));

        //We consider this as if the character is itself
        if(t_module <= 0.5)
            continue;

        if(t_shortestModule==0){
            t_shortestModule = t_module;
            t_closestPlayer = t_currentPlayer;
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

// Returns the distance to the closest character
float PhysicsManager::getDistanceToClosestCharacter(b2Vec2 p_p1){
    Character* t_closestPlayer = getClosestCharacter(p_p1);
    float t_target_x, t_target_y, t_target_z;
    if(t_closestPlayer!=0){
        t_target_x = t_closestPlayer->getX();
        t_target_y = t_closestPlayer->getY();
        t_target_z = t_closestPlayer->getZ();
    

        b2Vec2 t_p2 = b2Vec2(t_target_x, t_target_y); 

        b2Vec2 t_p2p1 = b2Vec2(t_target_x - p_p1.x, t_target_y - p_p1.y);

        float t_module = sqrt(pow(t_p2p1.x,2) + pow(t_p2p1.y,2));

        return(t_module);
    }

    return 0;
}

// Returns the distance between 2 points
float PhysicsManager::getDistanceBetween(b2Vec2 p_p1, b2Vec2 p_p2){
    float t_total_x = p_p2.x - p_p1.x;
    float t_total_y = p_p2.y - p_p1.y;
    float t_distance = abs(sqrt(pow(t_total_x,2) + pow(t_total_y, 2)));
    return t_distance;
}

ContactManager* PhysicsManager::getContactManager(){
    return m_contactManager;
}

void PhysicsManager::applyImpulse(int p_idBody, int t_side){
    b2Body* t_body = getBody(p_idBody);
    t_body->SetLinearDamping(1);
    t_body->ApplyLinearImpulse(b2Vec2(1000*t_side, 500), b2Vec2(t_body->GetWorldCenter()), false);
}

//The p_body is the body that realize the action/atak
bool PhysicsManager::checkCollisionSimple(b2Body* p_body, bool p_stun){
    for(int i = 0; i < m_playersBody.size(); i++){
        //Not the same body we pass to the function
        b2Body* t_body = m_playersBody.at(i);
        if(t_body != p_body){
            //We need to save the FixtureSensor because it stores the data of the Character.
            b2Fixture* fixtureA = p_body->GetFixtureList();
            if(fixtureA->IsSensor())
                fixtureA = fixtureA->GetNext();

            b2Fixture* fixtureB = t_body->GetFixtureList();
            b2Fixture* fixtureBsensor;
            if(fixtureB->IsSensor()){
                fixtureBsensor = fixtureB;
                fixtureB = fixtureB->GetNext();
            }else
                fixtureBsensor = fixtureB->GetNext();

            if(fixtureCollide(*fixtureA, *fixtureB)){
                //The fictures collide
                Character* t_player = static_cast<Character*>(fixtureBsensor->GetUserData());
                if(p_stun)
                    t_player->setStunned();
                t_player->receiveAttack(15, false);
                return true;
            }
        }
    }
    return false;
}

void PhysicsManager::checkCollisionMultiple(b2Body* p_body, b2Body* p_ignoreBody){
    for(int i = 0; i < m_playersBody.size(); i++){
        //Not the same body we pass to the function
        b2Body* t_body = m_playersBody.at(i);
        if(t_body != p_ignoreBody){
            //We need to save the FixtureSensor because it stores the data of the Character.
            b2Fixture* fixtureA = p_body->GetFixtureList();
            if(fixtureA->IsSensor())
                fixtureA = fixtureA->GetNext();

            b2Fixture* fixtureB = t_body->GetFixtureList();
            b2Fixture* fixtureBsensor;
            if(fixtureB->IsSensor()){
                fixtureBsensor = fixtureB;
                fixtureB = fixtureB->GetNext();
            }else
                fixtureBsensor = fixtureB->GetNext();

            //The fictures collide
            if(fixtureCollide(*fixtureA, *fixtureB)){
                Character* t_player = static_cast<Character*>(fixtureBsensor->GetUserData());
                //Calculate the side of the knocback
                float t_mainBodyX    = p_ignoreBody->GetPosition().x;
                float t_contactBodyX = t_body->GetPosition().x;
                int t_side = 1;
                if(t_mainBodyX > t_contactBodyX)
                    t_side = -1;
                t_player->setKnockback();
                t_body->SetLinearDamping(1);
                t_body->ApplyLinearImpulse(b2Vec2(1000*t_side,500), b2Vec2(t_body->GetWorldCenter()), false);
                t_player->receiveAttack(15, false);
            }
        }
    }
}

bool PhysicsManager::fixtureCollide(b2Fixture& fixtureA, b2Fixture& fixtureB){
    b2Shape* shapeA = fixtureA.GetShape();
    b2Shape* shapeB = fixtureB.GetShape();
    if(shapeA->GetType() == b2Shape::e_polygon && shapeB->GetType() == b2Shape::e_polygon){
        b2Body*             bodyA = fixtureA.GetBody();
        const b2Transform&  xfA   = bodyA->GetTransform();

        b2Body*             bodyB = fixtureB.GetBody();
        const b2Transform&  xfB   = bodyB->GetTransform();
        bool t_bool = b2TestOverlap(shapeA, 0, shapeB, 0, xfA, xfB);
        return t_bool;
    }
    return false;
}

void PhysicsManager::shockwaveBox(int p_idBody){
    b2Body* p_body = getBody(p_idBody);

    //Create a new body and positioning it in the coords of the Entity
    b2BodyDef* t_bodyDef = new b2BodyDef();
    t_bodyDef->type = b2_dynamicBody;
    t_bodyDef->position.Set(p_body->GetPosition().x, p_body->GetPosition().y);
    b2Body* t_body = m_world->CreateBody(t_bodyDef);

    //Create a shape for the body
    b2PolygonShape* t_polygonShape = new b2PolygonShape();
    t_polygonShape->SetAsBox(20.0, 20.0);
    
    b2FixtureDef* t_fixtureDef = new b2FixtureDef();
    t_fixtureDef->shape = t_polygonShape;

    //Attach the shape to the body
    t_body->CreateFixture(t_fixtureDef);

    //Check collision with the other players
    checkCollisionMultiple(t_body, p_body);
    
    m_world->DestroyBody(t_body);
}

void PhysicsManager::sparkyJump(int p_idBody){
    b2Body* p_body = getBody(p_idBody);

    p_body->SetLinearDamping(-1);
    //p_body->SetTransform(b2Vec2(0,50), 0);
}

void PhysicsManager::fastGravity(int p_idBody){
    b2Body* p_body = getBody(p_idBody);

    p_body->ApplyForce(b2Vec2(100,0), p_body->GetWorldCenter(), false);   
}

void PhysicsManager::machineGun(int p_idBody, bool p_orientation){
    b2Body* p_body = getBody(p_idBody);

    //Create a new body and positioning it in the coords of the Entity
    b2BodyDef* t_bodyDef = new b2BodyDef();
    t_bodyDef->type = b2_dynamicBody;
    t_bodyDef->position.Set(p_body->GetPosition().x, p_body->GetPosition().y);
    b2Body* t_body = m_world->CreateBody(t_bodyDef);

    //Create a shape for the body
    b2PolygonShape* t_polygonShape = new b2PolygonShape();
    if(p_orientation)
        t_polygonShape->SetAsBox(50.0, 5.0, b2Vec2(30,0), 0);
    else
        t_polygonShape->SetAsBox(50.0, 5.0, b2Vec2(-30,0), 0);
    
    b2FixtureDef* t_fixtureDef = new b2FixtureDef();
    t_fixtureDef->shape = t_polygonShape;

    //Attach the shape to the body
    t_body->CreateFixture(t_fixtureDef);

    //Check collision with the other players
    checkCollisionMultiple(t_body, p_body);
    
    m_world->DestroyBody(t_body);
}