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

#ifndef CHARACTER
#define CHARACTER

#include <SFML/Window.hpp>
#include "Entity.hpp"

class Character : public Entity{
public:
    Character(float p_position[3], char* p_name, int p_life, int p_damage, float p_velocity, bool p_orientation);
    ~Character();
	
    virtual void    jump();
	virtual void    basicAttack();
    virtual void    specialAttack(int p_index);
    virtual void    ultimateAttack();
    void            lookLeft();
    void            lookRight();
    void            playerInput();
    void            reciveAttack(int p_damage, bool p_orientation, bool p_block, float p_force);

protected: 
    char*   m_name;
    int     m_life;
    int     m_damage;
    float   m_velocity;
    float   m_atackPosition[3];
    bool    m_orientation;
    bool    m_stunned;
    bool    m_blocking;
    float   m_frameDeltaTime;               //For movement
    
    int             m_runningFactor;

    //Jumps
    bool            m_jumping;              // Controls if the jump is still going
    int             m_jumpCurrentTime;      // Control variable. Checks in which frame of the jump the character is in
    int             m_jumpMaxTime;          // Control the time in which the character is in the air (in frames)
    float           m_jumpTable[10];        // Determines how high the player goes each frame while jumping

    sf::Event       m_event;
};

#endif