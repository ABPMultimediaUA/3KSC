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
#include "../headers/managers/SoundManager.hpp"
//#include <vector>

class Character : public Entity{
public:
    Character(char* p_name, float p_position[3], int p_joystick, int p_life, int p_magic, int p_damage, float p_velocity, const char* p_modelURL);
    ~Character();
	
    void            receiveAttack(int p_damage, bool p_block, float p_force);
    virtual void    changeLife(int p_variation);
    void            changeMagic(int p_variation);
    void            shield();
    void            wings();
    void            die();
    void            lookLeft();
    void            lookRight();
    bool            isJumping();
    void            assignJoystick(int p_joystick);
    void            playerInput();
    void            playerUpdate();

    virtual void    jump();
    void            pickItem();
	virtual void    basicAttack();
    virtual void    specialAttackUp();
    virtual void    specialAttackDown();
    virtual void    specialAttackSide();
    virtual void    ultimateAttack();

    static int          getPlayerCount();
    static Character*   getPlayer(int p_index);
    int                 getIndex();


protected:
    static Character**  m_players;
    static int          m_playerCount;
    int                 m_playerIndex;

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
    float           m_frameDeltaTime;       //For movement
    
    int             m_runningFactor;

    //Jumps
    bool            m_jumping;              // Controls if the jump is still going
    int             m_jumpCurrentTime;      // Control variable. Checks in which frame of the jump the character is in
    int             m_jumpMaxTime;          // Control the time in which the character is in the air (in frames)
    float           m_jumpTable[10];        // Determines how high the player goes each frame while jumping

    bool            m_basicAttack;
    bool            m_specialAttackUp;
    bool            m_specialAttackDown;
    bool            m_specialAttackSide;
    bool            m_ultimateAttack;

    Projectile**    m_projectiles;
    int             m_maxProjectiles;
    int             m_currentProjectiles;

    SoundManager*   m_soundManager;
    Sound soundSteps;

private:
    //Conditions for each Input (they change depending on keyboard/joystick control)
    bool            m_upInput;
    bool            m_downInput;
    bool            m_leftInput;
    bool            m_rightInput;
    bool            m_jumpInput;
    bool            m_runInput;
    bool            m_blockInput;
    bool            m_pickInput;
    bool            m_basicAttackInput;
    bool            m_specialAttackUpInput;
    bool            m_specialAttackDownInput;
    bool            m_specialAttackSideInput;
    bool            m_ultimateAttackInput;

    void            updateInputs();
    void            checkActions();
    int             m_joystick;                 //[0,3]: Joystick   -1: Keyboard   -2: NPC
};

#endif