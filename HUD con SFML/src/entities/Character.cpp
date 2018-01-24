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


#include "../headers/entities/Character.hpp"
#include "../headers/managers/InputManager.hpp"
#include "../headers/managers/UIManager.hpp"
#include "../headers/extra/Keycodes.hpp"
#include "../headers/extra/Axis.hpp"
#include "../headers/extra/Buttons.hpp"
#include <iostream>

Character::Character(){
    m_maxLife               = 100;
    m_maxLifeShield         = 25;
    m_maxMagic              = 100;
    m_life                  = m_maxLife;
    m_lifeShield            = 0;
    m_magic                 = m_maxMagic;

    m_specialAttackUp       = false;
    m_specialAttackDown     = false;
    m_specialAttackSide     = false;
    m_ultimateAttack        = false;

    m_waitRelease           = false;
}

Character::~Character(){}

//Receives an attack from other player
//Parameters: damage, can you block it?
void Character::receiveAttack(int p_damage){
    changeLife(-p_damage);
    std::cout << "You took an attack and now have " << m_life << " HP." << std::endl << std::endl;
}

//Increases or decreases life
void Character::changeLife(int p_variation){
    //Decrease first Kira's life shield
    if (p_variation < 0 && m_lifeShield > 0){
        m_lifeShield += p_variation;
        
        if (m_lifeShield < 0){
            m_life += m_lifeShield;
            m_lifeShield = 0;
        }
    }

    //Life increase or no life shield
    else{
        m_life += p_variation;
    }

    if (m_life <= 0){
        m_life = 0;
        die();
    }
    
    else if (m_life > m_maxLife){
        m_life = m_maxLife;
    }

    //HUD Stuff
    //UIManager::instance()->setLife(m_playerIndex, m_life);
}

//Increases or decreases magic
void Character::changeMagic(int p_variation){
    m_magic += p_variation;

    if (m_magic < 0)
        m_magic = 0;
    
    else if (m_magic > m_maxMagic)
        m_magic = m_maxMagic;

    //HUD Stuff
}

//Resets life and magic
void Character::die(){
    m_life = m_maxLife;
    m_lifeShield = 0;
    m_magic = m_maxMagic;

    //UIManager::instance()->setLife(m_playerIndex, m_life);
}


//Updates joysticks state and booleans for each action
void Character::updateInputs(){
    InputManager* t_inputManager = InputManager::instance();
    
    //Keyboard input  
        /* Controls:
            *   X + Up/W                    Up Special Attack
            *   X + Down/S                  Down Special Attack
            *   X + Left/Right or A/D       Side Special Attack
            *   Z                           Ultimate Attack
        */

        m_upInput = t_inputManager->isKeyPressed(Key_W) || t_inputManager->isKeyPressed(Key_Up);
        m_downInput = t_inputManager->isKeyPressed(Key_S) || t_inputManager->isKeyPressed(Key_Down);
        m_leftInput = t_inputManager->isKeyPressed(Key_A) || t_inputManager->isKeyPressed(Key_Left);
        m_rightInput = t_inputManager->isKeyPressed(Key_D) || t_inputManager->isKeyPressed(Key_Right);
        
        m_specialAttackUpInput = t_inputManager->isKeyPressed(Key_X) && m_upInput;
        m_specialAttackDownInput = t_inputManager->isKeyPressed(Key_X) && m_downInput;
        m_specialAttackSideInput = t_inputManager->isKeyPressed(Key_X) && (m_leftInput || m_rightInput);
        m_ultimateAttackInput = t_inputManager->isKeyPressed(Key_Z);
}

//Calls action functions when they are active
void Character::checkActions(){
    if (m_specialAttackUp)
        specialAttackUp();

    if (m_specialAttackDown)
        specialAttackDown();

    if (m_specialAttackSide)
        specialAttackSide();

    if (m_ultimateAttack)
        ultimateAttack();
}

void Character::playerInput(){
    InputManager* t_inputManager = InputManager::instance();
    updateInputs();    

    //Special attack up
    if(m_specialAttackUpInput){
        if (!m_waitRelease){
            m_specialAttackUp = true;
            m_waitRelease = true;
        }
    }

    //Special attack down
    else if(m_specialAttackDownInput){
        if (!m_waitRelease){
            m_specialAttackDown = true;
            m_waitRelease = true;
        }
    }

    //Special attack side
    else if(m_specialAttackSideInput){
        if (!m_waitRelease){
            m_specialAttackSide = true;
            m_waitRelease = true;
        }
    }

    //Ultimate Attack
    else if(m_ultimateAttackInput){
        if (!m_waitRelease){
            m_ultimateAttack = true;
            m_waitRelease = true;
        }
    }

    //No attack
    else{
        m_waitRelease = false;
    }

    checkActions();    
}

//Update state of player
void Character::playerUpdate(){
    //Increase magic every second

}

//Life shield
void Character::specialAttackUp(){

}

void Character::specialAttackDown(){

}

void Character::specialAttackSide(){

}

void Character::ultimateAttack(){

}

//Returns the life of the player
int Character::getLife(){
    return m_life;
}

//Returns the life shield of the player
int Character::getLifeShield(){
    return m_lifeShield;
}

//Returns the magic of the player
int Character::getMagic(){
    return m_magic;
}