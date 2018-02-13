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
#include <vector>
#include <Box2D.h>

class PhysicsManager{
    private:
    static PhysicsManager* m_instance;
    //Entity** m_physicBodies;
    std::vector<b2Body*> m_physicBodies;

    b2Vec2*     m_gravity;
    b2World*     m_world;
    
    b2BodyDef*      m_bodyDef;
    b2Body*         m_body;
    b2PolygonShape* m_polygonShape;
    b2FixtureDef*   m_fixtureDef;

    int32   m_velocityIterations;
    int32   m_positionIterations;
    float32 m_timeStep;
    //int*    m_id;

    public:
    static PhysicsManager* instance();
    PhysicsManager();
    ~PhysicsManager();
    
    void createPhysicBoxPlayer(int* p_id, float p_position[3], float p_dimX, float p_dimY);
    void createPhysicBoxPlatform(int* p_id, float p_position[3], float p_scale[3], int p_arenaIndex);

    void addForce();
    void removeForce();
    void updateGravity();

    float RaycastBetween(b2Vec2 p_p1, b2Vec2 p_p2);

    b2World*        getWorld();
    b2PolygonShape* getShape(int p_id);
    b2Body*         getBody(int p_id);
    void            destroyBody(int p_id);
    int32           getVelocityIterations();
    int32           getPositionIterations();
    float32         getTimeStep();
};

#endif