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

class Character{
public:
    Character();
    ~Character();
	
    void            receiveAttack(int p_damage);
    virtual void    changeLife(int p_variation);
    void            changeMagic(int p_variation);
    void            die();
    void            playerInput();
    void            playerUpdate();

    virtual void    specialAttackUp();
    virtual void    specialAttackDown();
    virtual void    specialAttackSide();
    virtual void    ultimateAttack();

    int             getLife();
    int             getLifeShield();
    int             getMagic();

protected:
    int             m_life;
    int             m_lifeShield;  
    int             m_magic;   
    int             m_maxLife;
    int             m_maxLifeShield;
    int             m_maxMagic;
    
    bool            m_basicAttack;
    bool            m_specialAttackUp;
    bool            m_specialAttackDown;
    bool            m_specialAttackSide;
    bool            m_ultimateAttack;

private:
    //Conditions for each Input (they change depending on keyboard/joystick control)
    bool            m_upInput;
    bool            m_downInput;
    bool            m_leftInput;
    bool            m_rightInput;
    bool            m_specialAttackUpInput;
    bool            m_specialAttackDownInput;
    bool            m_specialAttackSideInput;
    bool            m_ultimateAttackInput;
    bool            m_waitRelease;

    void            updateInputs();
    void            checkActions();
};

#endif