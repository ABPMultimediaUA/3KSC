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


//Instance initialization
PhysicsManager* PhysicsManager::m_instance = 0;

//Returns the only instance of this class
PhysicsManager* PhysicsManager::instance(){
    if (!m_instance)
        m_instance = new PhysicsManager();

    return m_instance;
}

//Constructor
PhysicsManager::PhysicsManager(){
    m_worldAABB = b2AABB();
    b2Vec2 t_upperBound(100.0f, 100.0f);
    b2Vec2 t_lowerBound(-100.0f, -100.0f);
    m_worldAABB.upperBound = t_upperBound;
    m_worldAABB.lowerBound = t_lowerBound;

    m_gravity = b2Vec2(0.0f, -10.0f);
    
    m_doSleep = true;

    m_world = new b2World(m_worldAABB, m_gravity, m_doSleep);
    //std::cout << "Es validoo? " << m_world->GetPairCount() << std::endl;

    m_timeStep = 1.0 / 60.0;
    m_iterations = 10;
}

b2World* PhysicsManager::getWorld(){
    return m_world;
}

float PhysicsManager::getTimeStep(){
    return m_timeStep;
}

int PhysicsManager::getIterations(){
    return m_iterations;
}

//Destructor
PhysicsManager::~PhysicsManager(){}

//Adds a force to an entity
void PhysicsManager::addForce(){

}

//Removes a force from an entity
void PhysicsManager::removeForce(){

}

//Handles gravity changes in Kawaiisaki map
void PhysicsManager::updateGravity(){

}