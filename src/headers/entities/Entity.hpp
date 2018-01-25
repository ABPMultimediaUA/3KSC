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

//#include "../Model.hpp"
//#include "../Texture.hpp"
//#include "../Hitbox.hpp"

class Entity {
public:
    Entity(float p_position[3]);
    Entity(float p_position[3], float p_scale, const char* p_modelURL, int p_type = 0);
    Entity(float p_position[3], float p_scale[3], const char* p_modelURL, int p_type = 0);
    ~Entity();
    void moveTo(float p_position[3]);
    void moveX(float p_variation);
    void moveY(float p_variation);
    void moveZ(float p_variation);
    bool checkCloseness(float* p_point, float p_range);
    int getId();
    float* getPosition();
    float getX();
    float getY();
    float getZ();

    void rotate(float degrees);

    void updatePosition(bool p_jumping, bool p_jointed);

    static int getEntityCount();
protected:
    static int m_entityCount;
    int        m_id; 
    float      m_position[3]; // [0] for x, [1] for y, [2] for z
    float      m_lastPosition[3]; // [0] for x, [1] for y, [2] for z
    const char* m_modelURL;
    //Model*     m_model;
    //Texture*   m_texture;
    //Hitbox*    m_hitbox;
    float      m_weight;
};

#endif