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

#include "../headers/entities/Rawr.hpp"
#include <iostream>

Rawr::Rawr(float p_position[3], char* p_name, int p_life, int p_damage, float p_velocity, bool p_orientation) : Character(p_position, p_name, p_life, p_damage, p_velocity, p_orientation){
    m_maxProjectiles        = 1;
    m_currentProjectiles    = 0;
    m_projectiles           = new Projectile*[m_maxProjectiles];
}

Rawr::~Rawr(){}

void Rawr::jump(){
    Character::jump();
}

void Rawr::basicAttack(){
    if (m_basicAttack){

        //PENDING IMPLEMENTATION
        std::cout << "Basic Attack" << std::endl;

        m_basicAttack = false;
    }
}

void Rawr::specialAttackUp(){
    if (m_specialAttackUp){

        //PENDING IMPLEMENTATION
        std::cout << "Special Attack Up" << std::endl;

        m_specialAttackUp = false;
    }
}

void Rawr::specialAttackDown(){
    if (m_specialAttackDown){

        //PENDING IMPLEMENTATION
        std::cout << "Special Attack Down" << std::endl;

        m_specialAttackDown = false;
    }
}

void Rawr::specialAttackSide(){
    if (m_specialAttackSide){
        if (m_currentProjectiles < m_maxProjectiles){
            if(m_orientation){   // Looking right
                // Attack 20 units to the right
                m_attackPosition[0] = m_position[0] + 20;
                m_attackPosition[1] = m_position[1];
                m_attackPosition[2] = m_position[2];

                m_attackTarget[0] = m_position[0] + 100;
                m_attackTarget[1] = m_position[1];
                m_attackTarget[2] = m_position[2];
            }
            else{   // Looking left
                // Attack 20 units to the right
                m_attackPosition[0] = m_position[0] - 20;
                m_attackPosition[1] = m_position[1];
                m_attackPosition[2] = m_position[2];

                m_attackTarget[0] = m_position[0] - 100;
                m_attackTarget[1] = m_position[1];
                m_attackTarget[2] = m_position[2];
            }

            //Create attack and increase projectile count
            m_projectiles[m_currentProjectiles++] = new Projectile(m_attackPosition, m_attackTarget, 60, 3, 100);
        }

        //Move projectiles, and delete them
        for (int i = 0; i < m_currentProjectiles; i++){
            if (!m_projectiles[i]->update()){
                m_currentProjectiles--;
                m_specialAttackSide = false;
            }
        }
    }
}


void Rawr::ultimateAttack(){
    if (m_ultimateAttack){

        //PENDING IMPLEMENTATION
        std::cout << "ULTIMATE TIME!!!" << std::endl;

        m_ultimateAttack = false;
    }
}