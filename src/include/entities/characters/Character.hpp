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

#include "Entity.hpp"
#include "Projectile.hpp"
#include "../debug.hpp"

struct ActionMapping;

class Character : public Entity{
public:
    Character(char* p_name, float p_position[3], int p_life, int p_magic, int p_damage, float p_velocity, const char* p_modelURL, bool p_debugMode);
    ~Character();
	
    void            receiveAttack(int p_damage, bool p_block);
    virtual void    changeLife(int p_variation);
    void            changeMagic(int p_variation);
    void            shield();
    void            wings();
    void            die();
    void            lookLeft();
    void            lookRight();
    bool            isJumping();
    void            input();
    void            update();
    void            respawn(float p_position[3]);
    
    int             getDamage();
    int             getIndex();
    char*           getName();
    int             getLife();
    
    //Actions
    void            left();
    void            right();
    void            jump();
    void            run();
    void            block();
    void            pick();
	virtual void    basicAttack();
    virtual void    specialAttackUp();
    virtual void    specialAttackDown();
    virtual void    specialAttackSide();
    virtual void    ultimateAttack();
    
    void            modeDebug();


protected:
    static int      m_playerCount;
    int             m_playerIndex;

    char*           m_name;
    int             m_lives;
    int             m_life;
    int             m_magic;     
    int             m_maxLife;
    int             m_maxMagic;
    int             m_damage;
    float           m_velocity;
    float           m_attackPosition[3];
    float           m_attackTarget[3];
    bool            m_orientation;
    bool            m_stunned;
    bool            m_blocking;
    bool            m_shielded;
    bool            m_winged;
    bool            m_alive;
    float           m_frameDeltaTime;       //For movement
    bool            m_respawning;
    float           m_runningFactor;

    //Jumps
    int             m_maxJumps;
    bool            m_jumping;              // Controls if the jump is still going
    int             m_jumpCurrentTime;      // Control variable. Checks in which frame of the jump the character is in
    int             m_jumpMaxTime;          // Control the time in which the character is in the air (in frames)
    float           m_jumpTable[10];        // Determines how high the player goes each frame while jumping
    int             m_jumpIndex;            //For double jump


    ActionMapping*  m_actions;
    void            mapActions();
    
    Projectile**    m_projectiles;
    int             m_maxProjectiles;
    int             m_currentProjectiles;

    Debug *playerDebug;
    bool            m_debugMode;

private:
    bool            m_waitRelease;
    void            doActions();
};

#endif