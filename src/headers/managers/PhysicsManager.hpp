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

#ifndef PHYSICS_MANAGER
#define PHYSICS_MANAGER

#include "../entities/Entity.hpp"
#include <iostream>
#include <irrlicht.h>


class PhysicsManager{
    private:
    static PhysicsManager* m_instance;
    Entity** m_physicBodies;
    float m_gravity;

    public:
    static PhysicsManager* instance();
    PhysicsManager();
    ~PhysicsManager();
    bool checkCollision(irr::scene::ISceneNode* one, irr::scene::ISceneNode* two);
    void addForce();
    void removeForce();
    void updateGravity();
};

#endif