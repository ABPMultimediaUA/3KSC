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
#include "../headers/managers/EngineManager.hpp"

Rawr::Rawr(float p_position[3], char* p_name, int p_life, int p_damage, float p_velocity, bool p_orientation) : Character(p_position, p_name, p_life, p_damage, p_velocity, p_orientation){
    m_projectiles           = new Projectile*[5];
    m_maxProjectiles        = 1;
    m_currentProjectiles    = 0;
}

Rawr::~Rawr(){}

void Rawr::jump(){
    // Start or continue jump movement
    if(m_jumping){
        if(m_jumpCurrentTime < m_jumpMaxTime){
            moveY(m_jumpTable[m_jumpCurrentTime++]);
        }
        else{                                                                       // Jump has ended. Starting to go down
            // Activate gravity
            // Check collision with the floor
            // If there is collision
            m_jumping = false;                                                          // We are on the floor. Reset jump
            m_jumpCurrentTime = 0;
        }
    }
}

void Rawr::basicAttack(){
    if (m_basicAttack){
        if (m_currentProjectiles < m_maxProjectiles){
            if(m_orientation){   // Looking right
                // Attack 20 units to the right
                m_atackPosition[0] = m_position[0] + 20;
                m_atackPosition[1] = m_position[1];
                m_atackPosition[2] = 0;
            }
            else{   // Looking left
                // Attack 20 units to the right
                m_atackPosition[0] = m_position[0] - 20;
                m_atackPosition[1] = m_position[1];
                m_atackPosition[2] = 0;
            }

            //Create attack and increase projectile count
            m_projectiles[m_currentProjectiles++] = new Projectile(m_atackPosition, m_orientation, 3, 60, 30);
        }

        //Move projectiles, and delete them
        for (int i = 0; i < m_currentProjectiles; i++){
            if (m_projectiles[i]->move() == false){
                m_currentProjectiles--;
                m_basicAttack = false;
            }
        }
    }
}

void Rawr::specialAttack(int p_index){

}

void Rawr::ultimateAttack(){

}