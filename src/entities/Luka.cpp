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

#include "../headers/entities/Luka.hpp"
#include <iostream>

Luka::Luka(char* p_name, float p_position[3], int p_joystick) : Character(p_name, p_position, p_joystick, 100, 100, 30, 50.f, "assets/models/characters/plup/plup.obj"){
    m_maxProjectiles        = 1;
    m_currentProjectiles    = 0;
    m_projectiles           = new Projectile*[m_maxProjectiles];
}

Luka::~Luka(){}

void Luka::jump(){
    Character::jump();
}

void Luka::basicAttack(){
    //PENDING IMPLEMENTATION
    std::cout << "Basic Attack" << std::endl;
    
    m_basicAttack = false;
}

void Luka::specialAttackUp(){
    //PENDING IMPLEMENTATION
    std::cout << "Special Attack Up" << std::endl;

    m_specialAttackUp = false;
}

void Luka::specialAttackDown(){
    //PENDING IMPLEMENTATION
    std::cout << "Special Attack Down" << std::endl;
    
    m_specialAttackDown = false;
}

void Luka::specialAttackSide(){
    //PENDING IMPLEMENTATION
    std::cout << "Special Attack Side" << std::endl;

    m_specialAttackSide = false;
}


void Luka::ultimateAttack(){
    //PENDING IMPLEMENTATION
    std::cout << "ULTIMATE TIME!!!" << std::endl;

    m_ultimateAttack = false;
}