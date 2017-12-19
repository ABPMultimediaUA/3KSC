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

#include "../headers/entities/Sparky.hpp"
#include <iostream>

Sparky::Sparky(float p_position[3], char* p_name, int p_life, int p_damage, float p_velocity, bool p_orientation, int p_joystick) : Character(p_position, p_name, p_life, p_damage, p_velocity, p_orientation, p_joystick){
    m_maxProjectiles        = 1;
    m_currentProjectiles    = 0;
    m_projectiles           = new Projectile*[m_maxProjectiles];
}

Sparky::~Sparky(){}

void Sparky::jump(){
    Character::jump();
}

void Sparky::basicAttack(){
    //PENDING IMPLEMENTATION
    std::cout << "Basic Attack" << std::endl;
    
    m_basicAttack = false;
}

void Sparky::specialAttackUp(){
    //PENDING IMPLEMENTATION
    std::cout << "Special Attack Up" << std::endl;

    m_specialAttackUp = false;
}

void Sparky::specialAttackDown(){
    //PENDING IMPLEMENTATION
    std::cout << "Special Attack Down" << std::endl;
    
    m_specialAttackDown = false;
}

void Sparky::specialAttackSide(){
    //PENDING IMPLEMENTATION
    std::cout << "Special Attack Side" << std::endl;

    m_specialAttackSide = false;
}


void Sparky::ultimateAttack(){
    //PENDING IMPLEMENTATION
    std::cout << "ULTIMATE TIME!!!" << std::endl;

    m_ultimateAttack = false;
}