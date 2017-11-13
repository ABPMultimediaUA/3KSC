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

//Constructor
PhysicsManager::PhysicsManager(){
    this->m_physicBodies = NULL;
    this->m_gravity;
}

//Destructor
PhysicsManager::~PhysicsManager(){}

//Checks if two entities have collided
void PhysicsManager::checkCollision(){

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