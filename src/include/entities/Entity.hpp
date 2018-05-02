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

#ifndef ENTITY
#define ENTITY

class EngineManager;
class PhysicsManager;
class InputManager;
//class Debug;

class Entity {
public:
    Entity(float p_position[3], float p_scale, const char* p_modelURL, int p_type = 0);
    ~Entity();
    void        moveTo(float p_position[3]);
    void        moveTo(float p_y, float p_x);
    void        moveX(float p_variation);
    void        moveY(float p_variation);
    void        moveZ(float p_variation);
    void        moveXY(float p_variationX, float p_variationY);
    bool        checkCloseness(float* p_point, float p_range);
    int         getId();
    float*      getPosition();
    float       getX();
    float       getY();
    float       getZ();
    void        setX(float p_position);
    void        setY(float p_position);
    void        rotate(float degrees);
    void        updatePosition();
    static int  getEntityCount();

    /*
    void        createDebug();
    void        updateDebug();
    */

protected:
    EngineManager*   m_engineManager;
    PhysicsManager*  m_physicsManager;
    InputManager*    m_inputManager;

    static int              m_entityCount;
    int                     m_id; 
    float                   m_position[3]; // [0] for x, [1] for y, [2] for z
    float                   m_lastPosition[3]; // [0] for x, [1] for y, [2] for z
    const char*             m_modelURL;
    //Model*                m_model;
    //Texture*              m_texture;
    //Hitbox*               m_hitbox;
    float                   m_weight;
    
    bool                    m_debugMode;
    int                     m_totalFixtures;
    //Debug*                  m_entityDebug[4];
};

#endif