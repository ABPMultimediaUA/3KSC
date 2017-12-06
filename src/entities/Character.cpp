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
#include "../headers/managers/EngineManager.hpp"

//#include <iostream>

Character::Character(float p_position[3], char* p_name, int p_life, int p_damage, float p_velocity, bool p_orientation):Entity(p_position){
    m_name                  = p_name;
    m_life                  = p_life;
    m_damage                = p_damage;
    m_velocity              = p_velocity;
    m_orientation           = p_orientation;

    m_runningFactor         = 1;

    m_jumping               = false;
    m_jumpCurrentTime       = 0;
    m_jumpMaxTime           = 10;
    m_jumpTable[0]          = 3.0f;
    m_jumpTable[1]          = 2.4f;
    m_jumpTable[2]          = 1.9f;
    m_jumpTable[3]          = 1.6f;
    m_jumpTable[4]          = 1.25f;
    m_jumpTable[5]          = 0.95;
    m_jumpTable[6]          = 0.75;
    m_jumpTable[7]          = 0.55;
    m_jumpTable[8]          = 0.35;
    m_jumpTable[9]          = 0.15;

    m_basicAttack           = false;
    m_specialAttackLeft     = false;
    m_specialAttackRight    = false;
    m_specialAttackUp       = false;
    m_ultimateAttack        = false;
}

Character::~Character(){}

void Character::jump(){}

void Character::basicAttack(){}

void Character::specialAttack(int p_index){}

void Character::ultimateAttack(){}

void Character::lookLeft(){
    m_orientation = false;
}

void Character::lookRight(){
    m_orientation = true;
}

void Character::playerInput(){
    InputManager* t_inputManager = InputManager::instance();
    m_frameDeltaTime = EngineManager::instance()->getFrameDeltaTime();

    //Exit
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        EngineManager::instance()->stop();

    //Jump
    // 10 frames going up, where gravity is disabled. Then gravity gets enabled again
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        m_jumping = true;     // Begin jump movement
    }

    m_runningFactor = 1;

    //Basic Attack
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
        m_basicAttack = true;
    }
    
    //Sprint
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
        m_runningFactor = 2;

    //Up
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        moveY(m_velocity * m_frameDeltaTime * m_runningFactor);
    }

    //Down
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        moveY(m_velocity * m_frameDeltaTime * m_runningFactor * -1);
    }

    //Left
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        moveX(m_velocity * m_frameDeltaTime * m_runningFactor * -1);
        lookLeft();
    }

    //Right
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        moveX(m_velocity * m_frameDeltaTime * m_runningFactor);
        lookRight();
    }

    jump();
    basicAttack();
}

